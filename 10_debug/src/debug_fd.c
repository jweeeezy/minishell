/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:34:33 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/11 14:40:23 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	debug_fds(int max)
{
	int	fd;
	int	flags;

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