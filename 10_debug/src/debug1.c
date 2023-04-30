/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:51:18 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 17:29:03 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	debug_print_t_heredoc(t_data *data)
{
	t_heredoc	*index;

	index = data->heredoc;
	if (DEBUG)
	{
		if (index != NULL)
		{
			printf("\nt_heredoc:\n");
			while (index != NULL)
			{
				printf("t_heredoc: node: %p ", index);
				printf("next: %p\n", index->next);
				printf("t_heredoc: full_path: [%s] ", index->full_path);
				printf("hash: [%lu] ", index->hash);
				printf("fd: [%d]\n", index->fd);
				printf("\n");
				index = index->next;
			}
			printf("\n");
		}
		else
		{
			printf("///no heredocs///\n");
		}
	}
}

void	debug_print_t_combine(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (DEBUG)
	{
		printf("t_combine: %p\n", data->combine);
		while (cnt < data->commands_to_process)
		{
			printf("t_combine: combined_str: [%s] order_number: [%i]\n",
				data->combine[cnt].combined_str,
				data->combine[cnt].command->order_numb);
			cnt++;
		}
		printf("\n");
	}
}

static int	is_fd_open(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	return (!(flags & FD_CLOEXEC));
}

void	debug_pipes_helper(int index, int **fd_pipes)
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
