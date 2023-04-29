/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:19:52 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/29 11:15:30 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for close(), dup2()
#include "minishell.h"	// needed for debug(), MACROS

#include <stdio.h>

void	child_handle_indirection(t_data *data)
{
	if (data->flag_infile == 1 || data->flag_heredoc == 1)
	{
		if (dup2(data->fd_infile, STDIN_FILENO) == ERROR)
		{
			perror("dup2");
		}
	}
}

void	child_handle_outdirection(t_data *data)
{
	if (data->flag_outfile == 1)
	{
		if (dup2(data->fd_outfile, STDOUT_FILENO) == ERROR)
		{
			perror("dup2");
		}
	}
}

static void	child_close_pipes_before(int **fd_pipes, int end)
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

static void	child_close_pipes_after(int **fd_pipes, int start)
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

void	child_prepare_pipes(t_data *data, int **fd_pipes, int index,
			int counter_pipes)
{
	if (index == 0)
	{
		child_handle_indirection(data);
		close(fd_pipes[0][0]);
		child_close_pipes_after(fd_pipes, index + 1);
		if (dup2(fd_pipes[0][1], STDOUT_FILENO) == ERROR)
		{
			perror("dup2");
		}
		close(fd_pipes[0][1]);
		debug_print_pipe_status(data, "child first process", fd_pipes);
		child_handle_outdirection(data);
	}
	else if (index == counter_pipes)
	{
		child_close_pipes_before(fd_pipes, index);
		close(fd_pipes[index - 1][1]);
		if (dup2(fd_pipes[index - 1][0], STDIN_FILENO) == ERROR)
		{
			perror("dup2");
		}
		close(fd_pipes[index - 1][0]);
		debug_print_pipe_status(data, "child last process", fd_pipes);
		child_handle_indirection(data);
		child_handle_outdirection(data);
	}
	else
	{
		child_close_pipes_before(fd_pipes, index);
		child_close_pipes_after(fd_pipes, index + 1);
		close(fd_pipes[index][0]);
		if (dup2(fd_pipes[index - 1][0], STDIN_FILENO) == ERROR)
		{
			perror("dup2");
		}
		child_handle_indirection(data);
		close(fd_pipes[index - 1][0]);
		if (dup2(fd_pipes[index][1], STDOUT_FILENO) == ERROR)
		{
			perror("dup2");
		}
		close(fd_pipes[index][1]);
		debug_print_pipe_status(data, "child middle process", fd_pipes);
		child_handle_outdirection(data);
	}
}
