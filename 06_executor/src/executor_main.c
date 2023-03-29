/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/27 12:13:01 by kvebers          ###   ########.fr       */
=======
/*   Updated: 2023/03/28 22:48:43 by jwillert         ###   ########          */
>>>>>>> develop
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor_private.h"	// needed for executor_*()

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
<<<<<<< HEAD
		free(data->child_pids);
=======
>>>>>>> develop
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
	if (data->commands_to_process == 0)
	{
		return (EXECUTED);
	}
	executor_init(data);
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

//	@todo Handle HEREDOC
//	@todo Handle REDIRECTION
//	@todo Handle waitpid errors!
