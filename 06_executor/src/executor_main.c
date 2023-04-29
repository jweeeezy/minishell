/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:42:44 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/29 13:03:52 by kvebers          ###   ########.fr       */
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
	int		index;
	int		exit_code;
	int		status;
	pid_t	pid;

	index = 0;
	exit_code = 0;
	if (data->flag_builtin_only == 1)
		return (EXECUTED);
	while (index < data->counter_processes)
	{
		pid = waitpid(data->child_pids[index], &status, 0);
		if (pid == -1)
		{
			//perror("waitpid");
			return (EXECUTED);
		}
		else if (pid == 0)
			continue ;
		else if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
		index += 1;
	}
	data->exit_status = exit_code;
	return (EXECUTED);
}

static void	executor_init(t_data *data)
{
	int	index;

	index = 0;
	data->counter_pipes = executor_count_pipes(data);
	data->counter_processes = data->counter_pipes + 1;
	data->counter_commands = executor_count_commands(data);
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
		return (EXECUTED);
	}
	debug_print_stage("simple execution", 1);
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
	return (EXECUTED);
}

int	executor(t_data *data)
{
	executor_init(data);
	if (data->counter_processes < 1)
	{
		if (redirector_handle_redirections(data, 0) == ERROR)
		{
			return (ERROR);
		}
		executor_parent(data, NULL, 0);
		data->exit_status = 1;
		return (EXECUTED);
	}
	if (data->child_pids == NULL)
	{
		return (ERROR);
	}
	debug_print_stage("executor", 0);
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
