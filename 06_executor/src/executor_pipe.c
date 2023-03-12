/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:35:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/11 21:08:35 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	executor_pipe(t_data *data)
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (ERROR);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (ERROR);
	}

	if (pid == 0)
	{
		close(fd[1]);

		// do something

		close(fd[0]);
	}

	else
	{
		close(fd[0]);

		// do something

		close(fd[1]);
		
	}
	return (0);
}
