/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/29 11:20:10 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close(), unlink()
#include <stdio.h>		// needed perror()

#include "libme.h"

void	executor_parent_close_pipes(t_data *data, int **fd_pipes)
{
	int	index;

	index = 0;
	if (DEBUG)
		sleep (5);
	while (index < data->index_processes)
	{
		close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index += 1;
	}
	//	if (data->index_processes == 0)
//	{
//		close(fd_pipes[data->index_processes][1]);
//	}
//	else if (data->index_processes == data->counter_pipes + 1)
//	{
//		close(fd_pipes[data->index_processes - 1][0]);
//	}
//	else
//	{
//		close(fd_pipes[data->index_processes - 1][0]);
//		close(fd_pipes[data->index_processes - 1][1]);
//	}
	if (DEBUG)
		printf("\nindex [%d] ", data->index_processes);
	debug_print_pipe_status(data, "parent closing", fd_pipes);
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

static void	handle_heredoc(t_data *data)
{
	t_heredoc	*temp;

	temp = NULL;
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
	data->fd_infile = -1;
}

void	executor_parent(t_data *data, int **fd_pipes, int index)
{
//	if (fd_pipes != NULL && data->counter_pipes != 0)
//	{
//		executor_parent_close_pipes(data, fd_pipes);
//	}
	ft_dummy((void *) fd_pipes);
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
