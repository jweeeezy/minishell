/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:19:52 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/29 15:19:17 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for close(), dup2()
#include "minishell.h"	// needed for debug(), MACROS

static void	child_close_pipes_before(int **fd_pipes, int end)
{
	int	index;

	index = 0;
	while (index < end && fd_pipes[index] != NULL)
	{
		if (index != end - 1)
			close(fd_pipes[index][0]);
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

void	child_prepare_pipes(int **fd_pipes, int index, int counter_pipes)
{
	if (index == 0)
	{
		close(fd_pipes[0][0]);
		child_close_pipes_after(fd_pipes, index + 1);
		debug_print_pipe_status("Child first", fd_pipes);
		dup2(fd_pipes[0][1], STDOUT_FILENO);
	}
	else if (index == counter_pipes)
	{
		close(fd_pipes[index - 1][1]);
		debug_print_pipe_status("Child LAST", fd_pipes);
		dup2(fd_pipes[index - 1][0], STDIN_FILENO);
	}
	else
	{
		close(fd_pipes[index][0]);
		child_close_pipes_before(fd_pipes, index);
		child_close_pipes_after(fd_pipes, index + 1);
		debug_print_pipe_status("Child Middle", fd_pipes);
		dup2(fd_pipes[index][1], STDOUT_FILENO);
		dup2(fd_pipes[index - 1][0], STDIN_FILENO);
	}
}
