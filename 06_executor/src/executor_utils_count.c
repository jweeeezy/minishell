/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:07:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/29 15:47:24 by kvebers          ###   ########.fr       */
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
		if (data->combine[index].command->order_numb == HERE_DOC
			|| data->combine[index].command->order_numb == QUOTED_HEREDOC)
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
			|| data->combine[index].command->order_numb == HERE_DOC
			|| data->combine[index].command->order_numb == QUOTED_HEREDOC)
		{
			counter_redirections += 1;
		}
		index += 1;
	}
	return (counter_redirections);
}

int	executor_count_commands(t_data *data)
{
	int	index;
	int	counter_commands;

	index = 0;
	counter_commands = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == STRING
			|| is_builtin(data->combine[index].command->order_numb) == 1)
		{
			counter_commands += 1;
		}
		index += 1;
	}
	return (counter_commands);
}
