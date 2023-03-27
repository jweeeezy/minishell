/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/27 12:13:01 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor_private.h"	// needed for executor_*()
#include <stdio.h>

int	executor_select_cmd(t_data *data, int **fd_pipes, int index)
{
	if (is_builtin(data->combine[index].command->order_numb) == 1)
	{
		if (executor_builtin(data, fd_pipes, index) == ERROR)
		{
			return (ERROR);
		}
	}
	else
	{
		if (executor_extern(data, fd_pipes, index) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

int	executor_wait_for_childs(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->counter_processes)
	{
		if (waitpid(data->child_pids[index], NULL, 0) == -1)
		{
			return (ERROR);
		}
		index += 1;
	}
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	data->counter_pipes = executor_count_pipes(data);
	data->counter_processes = executor_count_processes(data);
	data->index_processes = 0;
	if (data->counter_pipes != 0)
	{
		if (executor_pipex(data) == ERROR)
		{
			return (ERROR);
		}
		if (executor_wait_for_childs(data) == ERROR)
		{
			free(data->child_pids);
			return (ERROR);
		}
		free(data->child_pids);
	}
	else
	{
		data->child_pids = malloc (sizeof(int) * data->counter_processes);
		if (data->child_pids == NULL)
		{
			return (ERROR);
		}
		if (executor_select_cmd(data, NULL, 0) == ERROR)
		{
			free(data->child_pids);
			return (ERROR);
		}
		if (wait(NULL) == -1)
		{
			free(data->child_pids);
			return (ERROR);
		}
		free(data->child_pids);
	}
	return (EXECUTED);
}

//	@todo Handle HEREDOC
//	@todo Handle REDIRECTION
//	@todo Handle waitpid errors!
