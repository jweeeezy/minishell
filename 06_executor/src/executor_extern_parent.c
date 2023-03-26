/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_extern_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/26 16:25:35 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close()
#include <stdio.h>		// needed perror()

int	executor_extern_parent_routine(t_data *data, int **fd_pipes)
{
	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		if (data->index_processes == 0)
			close (fd_pipes[data->index_processes][1]);
		else if (data->index_processes == data->counter_pipes + 1)
		{
			close(fd_pipes[data->index_processes - 1][0]);
		}
		else
		{
			close(fd_pipes[data->index_processes - 1][0]);
			close(fd_pipes[data->index_processes - 1][1]);
		}
		debug_print_pipe_status("|| IN PARENT ||", fd_pipes);
	}
	if (wait(NULL) == -1)
	{
		perror("wait");
		return (ERROR);
	}
	return (EXECUTED);
}
