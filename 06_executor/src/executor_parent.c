/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:25:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/14 13:03:41 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for close()
#include <stdio.h>		// needed perror()

void	executor_parent(t_data *data, int **fd_pipes, int index)
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
		debug_print_pipe_status("Parent", fd_pipes);
	}
	free(data->combine[index].command->full_path);
	data->combine[index].command->full_path = NULL;
}
