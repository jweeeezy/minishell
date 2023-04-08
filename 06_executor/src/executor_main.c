/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/08 13:45:51 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor_private.h"	// needed for executor_*()
#include <stdio.h>

static int	executor_wait_for_childs(t_data *data)
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

static void	executor_init(t_data *data)
{
	data->counter_pipes = executor_count_pipes(data);
	data->counter_processes = executor_count_processes(data);
	data->index_processes = 0;
	data->child_pids = malloc (sizeof (int) * data->counter_processes);
}

static int	executor_crossroads(t_data *data)
{
	// @note prob need to prehandle here in between pipes
	if (data->counter_pipes != 0)
	{
		if (executor_pipex(data) == ERROR)
		{
			return (ERROR);
		}
		if (executor_wait_for_childs(data) == ERROR)
		{
			return (ERROR);
		}
	}
	else
	{
		if (executor_cmd_selector(data, NULL, 0) == ERROR)
		{
			return (ERROR);
		}
		if (data->counter_processes != 0)
		{
			if (wait(NULL) == -1)
				return (ERROR);
		}
	}
	return (EXECUTED);
}

int	executor(t_data *data)
{
	//if (data->commands_to_process == 0)
	//{
	//	return (EXECUTED);
	//}
	executor_init(data);
	printf("counter_processes: %d\n", data->counter_processes);
	if (data->counter_processes < 1)
	{
		return (EXECUTED);
	}
	if (data->child_pids == NULL)
	{
		return (ERROR);
	}
	if (executor_crossroads(data) == ERROR)
	{
		free(data->child_pids);
		data->child_pids = NULL;
		return (ERROR);
	}
	free(data->child_pids);
	data->child_pids = NULL;
	return (EXECUTED);
}
