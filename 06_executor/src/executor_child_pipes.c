/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:13:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:40:07 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for close(), dup2()
#include <stdio.h>		// needed for perror()
#include "minishell.h"	// needed for t_data, MACROS
#include "executor.h"	// needed for child_*()

static void	child_first_process(t_data *data, int **fd_pipes, int index)
{
	child_handle_indirection(data);
	close(fd_pipes[0][0]);
	child_close_pipes_after(fd_pipes, index + 1);
	if (dup2(fd_pipes[0][1], STDOUT_FILENO) == ERROR
		&& data->flag_printed == 0)
	{
		perror("dup2");
	}
	close(fd_pipes[0][1]);
	child_handle_outdirection(data);
}

static void	child_last_process(t_data *data, int **fd_pipes, int index)
{
	child_close_pipes_before(fd_pipes, index);
	close(fd_pipes[index - 1][1]);
	if (dup2(fd_pipes[index - 1][0], STDIN_FILENO) == ERROR
		&& data->flag_printed == 0)
		perror("dup2");
	close(fd_pipes[index - 1][0]);
	child_handle_indirection(data);
	child_handle_outdirection(data);
}

static void	child_middle_process(t_data *data, int **fd_pipes, int index)
{
	child_close_pipes_before(fd_pipes, index);
	child_close_pipes_after(fd_pipes, index + 1);
	close(fd_pipes[index][0]);
	if (dup2(fd_pipes[index - 1][0], STDIN_FILENO) == ERROR
		&& data->flag_printed == 0)
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
	child_handle_outdirection(data);
}

void	child_prepare_pipes(t_data *data, int **fd_pipes, int index,
			int counter_pipes)
{
	if (index == 0)
	{
		child_first_process(data, fd_pipes, index);
	}
	else if (index == counter_pipes)
	{
		child_last_process(data, fd_pipes, index);
	}
	else
	{
		child_middle_process(data, fd_pipes, index);
	}
}
