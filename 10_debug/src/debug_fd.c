/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:34:33 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:30:19 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	is_fd_open(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	return (!(flags & FD_CLOEXEC));
}

void	debug_print_fds(int max)
{
	int	fd;
	int	flags;

	if (DEBUG)
	{
		fd = 0;
		flags = -1;
		printf("List of used fd:\n");
		while (fd < max)
		{
			flags = fcntl(fd, F_GETFL);
			if (flags != -1)
			{
				printf("%d\n", fd);
			}
			fd += 1;
		}
	}
}

static void	debug_pipes_helper(int index, int **fd_pipes)
{
	if (is_fd_open(fd_pipes[index][0]) == 1)
		printf("fd_pipes[%d][0] is OPEN == 1\n", index);
	else
		printf("fd_pipes[%d][0] is CLOSED == 0\n", index);
	if (is_fd_open(fd_pipes[index][1]) == 1)
		printf("fd_pipes[%d][1] is OPEN == 1\n", index);
	else
		printf("fd_pipes[%d][1] is CLOSED == 0\n", index);
}

void	debug_print_pipe_status(t_data *data, char *message, int **fd_pipes)
{
	int	index;

	index = 0;
	if (DEBUG)
	{
		if (dup2(data->fd_stdout, STDOUT_FILENO) == ERROR)
			perror("dup2");
		if (fd_pipes == NULL)
		{
			printf("///no pipes///\n\n");
			return ;
		}
		printf("fd_pipes: <%s> %p\n", message, fd_pipes);
		while (fd_pipes[index] != NULL)
		{
			debug_pipes_helper(index, fd_pipes);
			index++;
		}
		printf("\n");
	}
}

void	debug_print_redirections(t_data *data)
{
	if (DEBUG)
	{
		if (data->flag_heredoc == 1 || data->flag_infile == 1
			|| data->flag_outfile == 1)
		{
			printf("redirections: \n");
			printf("redirections: flag_heredoc: [%d] ", data->flag_heredoc);
			printf("flag_infile: [%d] ", data->flag_infile);
			printf("flag_outfile: [%d]\n", data->flag_outfile);
			printf("redirections: fd_infile: [%d] ", data->fd_infile);
			printf("                    fd_outfile: [%d]\n",
				data->fd_outfile);
		}
		else
		{
			printf("///no redirections///\n\n");
			return ;
		}
		printf("\n");
	}
}
