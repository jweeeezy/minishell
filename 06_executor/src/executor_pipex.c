/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:47:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/26 16:15:58 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include "executor_private.h"	// needed for UTILS_IS
#include <unistd.h>		// needed for pipe()


static int	pipex_skip_non_commands(t_combine *cmd, int index)
{
	while (executor_is_pipe(&cmd[index]) == 1
		|| executor_is_redirection(&cmd[index]) == 1
		|| executor_is_heredoc(&cmd[index]) == 1)
	{
		index += 1;
	}
	return (index);
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
	while (index < data->counter_pipes + data->counter_pipes + 1)
	{
		index += pipex_skip_non_commands(data->combine, index);
		if (executor_select_cmd(data, fd_pipes, index) == ERROR)
		{
			free_pipe_array(fd_pipes, data->counter_pipes);
			return (ERROR);
		}
		index += 1;
		data->index_processes += 1;
	}
	free_pipe_array(fd_pipes, data->counter_pipes);
	return (EXECUTED);
}
