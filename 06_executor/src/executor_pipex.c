/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:47:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:14:49 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"		// needed for malloc(), NULL
#include "minishell.h"	// needed for t_data, MACROS
#include "executor.h"	// needed for executor_*(), pipex_*()

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

static void	re_init_fd(t_data *data)
{
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->flag_infile = 0;
	data->flag_outfile = 0;
}

int	executor_pipex(t_data *data)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = pipex_create_pipes(data->counter_pipes);
	if (fd_pipes == NULL)
		return (ERROR);
	while (index < data->commands_to_process)
	{
		data->exit_status = 0;
		if (executor_cmd_selector(data, fd_pipes, index) == ERROR)
		{
			free_pipe_array(fd_pipes, data->counter_pipes);
			return (ERROR);
		}
		index = pipex_advance_to_next_pipe(data, index);
		re_init_fd(data);
	}
	if (fd_pipes != NULL && data->counter_pipes != 0)
		executor_parent_close_pipes(data, fd_pipes);
	free_pipe_array(fd_pipes, data->counter_pipes);
	return (EXECUTED);
}
