/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:51:18 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/29 16:29:36 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	debug_print_pid(char *process_name)
{
	int	pid;

	pid = getpid();
	if (DEBUG)
	{
		printf("%s: pid[%d]\n", process_name, pid);
		printf("\n");
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

void	debug_print_pipe_status(char *message, int **fd_pipes)
{
	int	index;

	index = 0;
	if (DEBUG)
	{
		printf("fd_pipes: <%s> %p\n", message, fd_pipes);
		while (fd_pipes[index] != NULL)
		{
			if (is_fd_open(fd_pipes[index][0]) == 1)
				printf("fd_pipes[%d][0] is OPEN == 1\n", index);
			else
				printf("[fd_pipes%d][0] is CLOSED == 0\n", index);
			if (is_fd_open(fd_pipes[index][1]) == 1)
				printf("fd_pipes[%d][1] is OPEN == 1\n", index);
			else
				printf("fd_pipes[%d][1] is CLOSED == 0\n", index);
			index++;
		}
		printf("\n");
	}
}
