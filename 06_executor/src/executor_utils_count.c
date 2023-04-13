/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:07:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/13 13:29:51 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS

int	executor_count_pipes(t_data *data)
{
	int	index;
	int	counter_pipes;

	index = 0;
	counter_pipes = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == PIPE
			|| data->combine[index].command->order_numb == LAST_PIPE)
		{
			counter_pipes += 1;
		}
		index += 1;
	}
	return (counter_pipes);
}

int	executor_count_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;

	index = 0;
	counter_heredocs = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == HERE_DOC)
		{
			counter_heredocs += 1;
		}
		index += 1;
	}
	return (counter_heredocs);
}

int	executor_count_redirections(t_data *data)
{
	int	index;
	int	counter_redirections;

	index = 0;
	counter_redirections = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == COMMAND_TO_FILE
			|| data->combine[index].command->order_numb == FILE_TO_COMMAND
			|| data->combine[index].command->order_numb == HERE_DOC)
		{
			counter_redirections += 1;
		}
		index += 1;
	}
	return (counter_redirections);
}

int	executor_count_processes(t_data *data)
{
	int	index;
	int	counter_processes;

	index = 0;
	counter_processes = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == STRING
			|| is_builtin(data->combine[index].command->order_numb) == 1)
		{
			counter_processes += 1;
		}
		index += 1;
	}
	return (counter_processes);
}
