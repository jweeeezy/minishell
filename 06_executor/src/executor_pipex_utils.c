/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:47:57 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:13:24 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS

int	pipex_skip_non_commands(t_data *data, int index)
{
	while ((index < data->commands_to_process
			&& data->combine[index].combined_str != NULL
			&& data->combine[index].command->order_numb != STRING
			&& is_builtin(data->combine[index].command->order_numb) == 0
			&& data->combine[index].command->order_numb != PIPE
			&& data->combine[index].command->order_numb != LAST_PIPE))
	{
		index += 1;
	}
	return (index);
}

int	pipex_advance_to_next_pipe(t_data *data, int index)
{
	index += 1;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].combined_str == NULL)
		{
			break ;
		}
		else if (data->combine[index].command->order_numb == PIPE
			|| data->combine[index].command->order_numb == LAST_PIPE)
		{
			data->index_processes += 1;
			index += 1;
			break ;
		}
		index += 1;
	}
	return (index);
}
