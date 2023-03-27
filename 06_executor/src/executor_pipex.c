/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:47:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/27 11:06:23 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include "executor_private.h"	// needed for UTILS_IS
#include <unistd.h>		// needed for pipe()

static int	pipex_skip_non_commands(t_data *data, t_combine *cmd, int index)
{
	int	offset;

	offset = 0;
	if (index >= data->commands_to_process)
	{
		return (offset);
	}
	if (executor_is_pipe(&cmd[index]) == 1
		|| executor_is_redirection(&cmd[index]) == 1
		|| executor_is_heredoc(&cmd[index]) == 1)
	{
		offset += 1;
	}
	return (offset);
}

static int	**pipex_create_pipes(int counter_pipes)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = malloc (sizeof (int *) * (counter_pipes + 1));
	if (fd_pipes == NULL)
	{
		return (NULL);
	}
	while (index < counter_pipes)
	{
		fd_pipes[index] = malloc (sizeof (int) * 2);
		if (fd_pipes[index] == NULL
			|| pipe(fd_pipes[index]) == ERROR)
		{
			free_pipe_array(fd_pipes, index);
			return (NULL);
		}
		index += 1;
	}
	fd_pipes[counter_pipes] = NULL;
	return (fd_pipes);
}

int	executor_pipex(t_data *data)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = pipex_create_pipes(data->counter_pipes);
	if (fd_pipes == NULL)
	{
		return (ERROR);
	}
	data->child_pids = malloc (sizeof (int) * data->counter_processes);
	if (data->child_pids == NULL)
	{
		free_pipe_array(fd_pipes, data->counter_pipes);
		return (ERROR);
	}
	while (index < data->commands_to_process)
	{
		if (executor_select_cmd(data, fd_pipes, index) == ERROR)
		{
			free(data->child_pids);
			free_pipe_array(fd_pipes, data->counter_pipes);
			return (ERROR);
		}
		index += 1;
		index += pipex_skip_non_commands(data, data->combine, index);
		data->index_processes += 1;
	}
	free_pipe_array(fd_pipes, data->counter_pipes);
	return (EXECUTED);
}
