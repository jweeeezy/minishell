/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/30 13:23:18 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close()
#include <stdio.h>		// needed perror()

static void	executor_parent_close_pipes(t_data *data, int **fd_pipes, int index)
{
	if (data->index_processes == 0)
	{
		close(fd_pipes[data->index_processes][1]);
	}
	else if (data->index_processes == data->counter_pipes + 1)
	{
		close(fd_pipes[data->index_processes - 1][0]);
	}
	else
	{
		close(fd_pipes[data->index_processes - 1][0]);
		close(fd_pipes[data->index_processes - 1][1]);
	}
}

void	executor_parent(t_data *data, int **fd_pipes, int index)
{
	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		executor_parent_close_pipes(data, fd_pipes, index);
		debug_print_pipe_status("Parent", fd_pipes);
	}
	if (flag_infile == 1)
	{
		close(fd_infile);
		flag_infile = 0;
	}
	if (flag_outfile == 1)
	{
		close(fd_outfile);
		flag_outfile = 0;
	}
	free(data->combine[index].command->full_path);
	data->combine[index].command->full_path = NULL;
}
