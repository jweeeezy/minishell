/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/27 11:27:10 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close(), unlink()
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
	t_heredoc	*temp;

	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		executor_parent_close_pipes(data, fd_pipes);
	}
	if (data->flag_infile == 1)
	{
		close(data->fd_infile);
		data->flag_infile = 0;
		dup2(data->fd_stdin, STDOUT_FILENO);
	}
	else if (data->flag_heredoc == 1)
	{
		unlink(data->heredoc->full_path);
		free(data->heredoc->full_path);
		if (data->heredoc->next == NULL)
		{
			free(data->heredoc);
			data->heredoc = NULL;
		}
		else
		{
			temp = data->heredoc;
			data->heredoc = data->heredoc->next;
			free(temp);
		}
		data->flag_heredoc = 0;
	}
	if (data->flag_outfile == 1)
	{
		close(data->fd_outfile);
		data->flag_outfile = 0;
		dup2(data->fd_stdout, STDOUT_FILENO);
	}
	if (data->combine[index].full_path != NULL)
	{
		free(data->combine[index].full_path);
	}
}
