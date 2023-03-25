/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:51:18 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/25 14:35:57 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

void	debuger(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		printf("%s ", data->combine[cnt].combined_str);
		printf("%i\n", data->combine[cnt].command->order_numb);
		cnt++;
	}
}

static int	is_fd_open(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	return !(flags & FD_CLOEXEC);
}

void	debug_print_pipe_status(char *message, int **fd_pipes)
{
	int	index;

	index = 0;
	if (DEBUG)
	{
		printf("%s\n", message);
		while (fd_pipes[index] != NULL)
		{
			if (is_fd_open(fd_pipes[index][0]) == 1)
				printf("pipefd[%d][0] is 1 - OPEN\n", index);
			else
				printf("pipefd[%d][0] is 0 - CLOSED\n", index);
			if (is_fd_open(fd_pipes[index][1]) == 1)
				printf("pipefd[%d][1] is 1 - OPEN\n", index);
			else
				printf("pipefd[%d][1] is 0 - CLOSED\n", index);
			index++;
		}
	}
}