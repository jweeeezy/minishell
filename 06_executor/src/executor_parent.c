/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:11:46 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close(), dup2(), unlink()

void	executor_parent_close_pipes(t_data *data, int **fd_pipes)
{
	int	index;

	index = 0;
	while (index < data->index_processes)
	{
		close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index += 1;
	}
}

static void	handle_outdirection(t_data *data)
{
	close(data->fd_outfile);
	data->flag_outfile = 0;
	dup2(data->fd_stdout, STDOUT_FILENO);
	data->fd_outfile = -1;
}

static void	handle_indirection(t_data *data)
{
	close(data->fd_infile);
	data->flag_infile = 0;
	dup2(data->fd_stdin, STDIN_FILENO);
	data->fd_infile = -1;
}

void	handle_heredoc(t_data *data)
{
	t_heredoc	*temp;

	temp = NULL;
	unlink(data->heredoc->full_path);
	free(data->heredoc->full_path);
	data->heredoc->full_path = NULL;
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
	data->fd_infile = -1;
}

void	executor_parent(t_data *data, int index)
{
	if (data->flag_infile == 1)
	{
		handle_indirection(data);
	}
	else if (data->flag_heredoc == 1)
	{
		handle_heredoc(data);
	}
	if (data->flag_outfile == 1)
	{
		handle_outdirection(data);
	}
	if (data->combine[index].full_path != NULL)
	{
		free(data->combine[index].full_path);
	}
}
