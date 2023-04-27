/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:25 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/27 13:09:00 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// needed for executor_child(),
						// executor_parent()
#include "minishell.h"	// needed for t_data
#include <unistd.h>		// needed for NULL, access()
#include "libft.h"		// needed for ft_split(), ft_strlen()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter()
#include <stdio.h>		// needed for printf()
#include "redirector.h"

int	child_execute_builtin(t_data *data, int index);

static int	selector_fork_and_execute(t_data *data, int **fd_pipes, int index,
				int flag_cmd)
{
	if (flag_cmd == ERROR)
	{
		executor_parent(data, fd_pipes, index);
		return (ERROR);
	}
	if (fd_pipes == NULL && flag_cmd == BUILTIN)
	{
		data->flag_builtin_only = 1;
		child_handle_indirection(data);
		child_handle_outdirection(data);
		if (child_execute_builtin(data, index) == ERROR)
		{
			return (ERROR);
		}
		executor_parent(data, fd_pipes, index);
		return (EXECUTED);
	}
	data->child_pids[data->index_processes] = fork();
	if (data->child_pids[data->index_processes] == -1)
	{
		executor_parent(data, fd_pipes, index);
		return (ERROR);
	}
	if (data->child_pids[data->index_processes] == 0)
	{
		executor_child(data, fd_pipes, index, flag_cmd);
	}
	else
	{
		executor_parent(data, fd_pipes, index);
	}
	return (EXECUTED);
}

int	executor_cmd_selector(t_data *data, int **fd_pipes, int index)
{
	int	return_value;

	if (redirector_handle_redirections(data, index) == ERROR)
	{
		return (ERROR);
	}
	index = pipex_skip_non_commands(data, index);
	if (index >= data->commands_to_process
		|| data->combine[index].command->order_numb == PIPE
		|| data->combine[index].command->order_numb == LAST_PIPE)
	{
		return (EXECUTED);
	}
	else if (data->fd_infile == -100)
	{
		data->fd_infile = -1;
		return_value = NO_EXECUTION;
	}
	else if (is_builtin(data->combine[index].command->order_numb) == 1)
	{
		return_value = BUILTIN;
	}
	else if (selector_is_cmd_path_valid(&data->combine[index]) == EXTERN)
	{
		return_value = EXTERN;
	}
	else
	{
		return_value = selector_is_cmd_valid(data, &data->combine[index],
				data->envp);
	}
	if (selector_fork_and_execute(data, fd_pipes, index, return_value) == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}
