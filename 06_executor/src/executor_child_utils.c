/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:19:52 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:54:16 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for close(), dup2()
#include <stdio.h>		// needed for perror()
#include "executor.h"	// needed for child_*()
#include "minishell.h"	// needed for debug(), MACROS

void	child_handle_indirection(t_data *data)
{
	if (data->flag_infile == 1 || data->flag_heredoc == 1)
	{
		if (dup2(data->fd_infile, STDIN_FILENO) == ERROR
			&& data->flag_printed == 0)
		{
			perror("dup2");
		}
	}
}

void	child_handle_outdirection(t_data *data)
{
	if (data->flag_outfile == 1)
	{
		if (dup2(data->fd_outfile, STDOUT_FILENO) == ERROR
			&& data->flag_printed == 0)
		{
			perror("dup2");
		}
	}
}

void	child_close_pipes_before(int **fd_pipes, int end)
{
	int	index;

	index = 0;
	while (index < end && fd_pipes[index] != NULL)
	{
		if (index != end - 1)
		{
			close(fd_pipes[index][0]);
		}
		close(fd_pipes[index][1]);
		index += 1;
	}
}

void	child_close_pipes_after(int **fd_pipes, int start)
{
	int	index;

	index = start;
	while (fd_pipes[index] != NULL)
	{
		close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index += 1;
	}
}

void	child_handle_pipes_and_redirections(t_data *data, int **fd_pipes)
{
	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		child_prepare_pipes(data, fd_pipes, data->index_processes,
			data->counter_pipes);
	}
	else
	{
		child_handle_outdirection(data);
		child_handle_indirection(data);
	}
}
