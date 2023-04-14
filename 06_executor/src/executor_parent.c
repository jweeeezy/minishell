/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/14 14:15:14 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close()
#include <stdio.h>		// needed perror()

static void	executor_parent_close_pipes(t_data *data, int **fd_pipes)
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
		executor_parent_close_pipes(data, fd_pipes);
		debug_print_pipe_status("Parent", fd_pipes);
	}
	if (data->flag_infile == 1)
	{
		close(data->fd_infile);
		data->flag_infile = 0;
	}
	if (data->flag_outfile == 1)
	{
		close(data->fd_outfile);
		data->flag_outfile = 0;
	}
	(void) index;
	if (data->flag_heredoc == 1)
	{
		free(data->heredoc->full_path);
		free(data->heredoc);
		data->heredoc = NULL;
	}
	if (data->combine[index].first_element != NULL)
		free(data->combine[index].first_element);
	if (data->combine[index].full_path != NULL)
		free(data->combine[index].full_path);
	//free(data->combine[index].command->full_path);
	//data->combine[index].command->full_path = NULL;
}
