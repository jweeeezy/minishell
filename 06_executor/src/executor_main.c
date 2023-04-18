/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by                   #+#    #+#             */
/*   Updated: 2023/04/18 18:54:28 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"			// needed for t_data, MACROS
#include "executor.h"	// needed for executor_*()
#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>	// linux
#include <sys/wait.h>	// linux

static int	executor_wait_for_childs(t_data *data)
{
	int	index;

	index = 0;
	if (data->flag_builtin_only == 1)
	{
		return (EXECUTED);
	}
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
	int	index;

	index = 0;
	data->counter_pipes = executor_count_pipes(data);
	data->counter_processes = executor_count_processes(data);
	data->index_processes = 0;
	data->child_pids = malloc (sizeof (int) * data->counter_processes);
	if (data->child_pids != NULL)
	{
		while (index < data->counter_processes)
		{
			data->child_pids[index] = 0;
			index += 1;
		}
	}
}

static int	executor_crossroads(t_data *data)
{
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
		if (data->counter_processes != 0 && data->flag_builtin_only == 0)
		{
			if (executor_wait_for_childs(data) == ERROR)
			{
				return (ERROR);
			}
		}
	}
	return (EXECUTED);
}

int	executor(t_data *data)
{
	executor_init(data);
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
