/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:34:33 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 17:28:19 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

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

void	debug_stepper(char *message)
{
	ft_putstr_fd(message, 2);
	sleep(2);
}

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
