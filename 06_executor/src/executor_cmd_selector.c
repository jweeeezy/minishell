/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:25 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:05:19 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for fork()
#include "minishell.h"	// needed for t_data, MACROS
#include "executor.h"	// needed for child_*()

static int	selector_handle_single_builtin(t_data *data, int index)
{
	data->flag_builtin_only = 1;
	child_handle_indirection(data);
	child_handle_outdirection(data);
	if (child_execute_builtin(data, index) == ERROR)
	{
		return (ERROR);
	}
	executor_parent(data, index);
	return (EXECUTED);
}

static int	selector_fork_and_execute(t_data *data, int **fd_pipes, int index,
				int flag_cmd)
{
	if (flag_cmd == ERROR)
	{
		executor_parent(data, index);
		return (ERROR);
	}
	if (fd_pipes == NULL && flag_cmd == BUILTIN)
	{
		return (selector_handle_single_builtin(data, index));
	}
	data->child_pids[data->index_processes] = fork();
	if (data->child_pids[data->index_processes] == -1)
	{
		executor_parent(data, index);
		return (ERROR);
	}
	child_signals();
	if (data->child_pids[data->index_processes] == 0)
	{
		executor_child(data, fd_pipes, index, flag_cmd);
	}
	else
	{
		executor_parent(data, index);
	}
	return (EXECUTED);
}

static int	find_cmd_type(t_data *data, int index)
{
	int	return_value;

	return_value = NO_EXECUTION;
	if (data->fd_infile == -100 || data->fd_outfile == -100)
	{
		return_value = NO_EXECUTION;
		if (data->fd_infile == -100)
			data->fd_infile = -1;
		if (data->fd_outfile == -100)
			data->fd_outfile = -1;
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
		return_value = selector_is_cmd_valid(&data->combine[index],
				data->envp);
	}
	return (return_value);
}

static int	executor_add_trailing_command(t_data *data, int index)
{
	int	offset;

	offset = index + 1;
	while (executor_is_t_combine_advanceable(data, offset) == 1)
	{
		if (data->combine[offset].command->order_numb == STRING
			|| is_builtin(data->combine[offset].command->order_numb) == 1
			|| data->combine[offset].command->order_numb == N
			|| data->combine[offset].command->order_numb == WIERD_N)
		{
			data->combine[offset].command->order_numb = WHITE;
			data->combine[index].combined_str
				= ft_charjoin(data->combine[index].combined_str, ' ', 0, 0);
			if (data->combine[index].combined_str == NULL)
				return (ERROR);
			data->combine[index].combined_str
				= ft_strjoin2(data->combine[index].combined_str,
					data->combine[offset].combined_str, 0, 0);
			if (data->combine[index].combined_str == NULL)
				return (ERROR);
		}
		offset += 1;
	}
	return (EXECUTED);
}

int	executor_cmd_selector(t_data *data, int **fd_pipes, int index)
{
	int	return_value;

	if (redirector_handle_redirections(data, index) == ERROR)
		return (ERROR);
	index = pipex_skip_non_commands(data, index);
	if (executor_add_trailing_command(data, index) == ERROR)
		return (ERROR);
	if (index >= data->commands_to_process
		|| data->combine[index].command->order_numb == PIPE
		|| data->combine[index].command->order_numb == LAST_PIPE)
		return (EXECUTED);
	return_value = find_cmd_type(data, index);
	if (return_value == COMMAND_NOT_FOUND)
		selector_print_command_not_found(data);
	if (selector_fork_and_execute(data, fd_pipes, index, return_value) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
