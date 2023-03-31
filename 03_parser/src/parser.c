/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/30 15:40:04 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	investigate_redirections(t_data *data, int cnt)
{
	(void) data;
	(void) cnt;
	return (EXECUTED);
}

int	investigate_quotes(t_data *data, int cnt)
{
	(void) data;
	(void) cnt;
	return (EXECUTED);
}


int	crime_scene_investigation(t_data *data, int cnt)
{
	while (cnt < data->commands_to_process)
	{
		if (cnt > 0)
		{
			if (data->combine[cnt - 1].command->order_numb == FILE_TO_COMMAND
				|| data->combine[cnt - 1].command->order_numb == COMMAND_TO_FILE
				|| data->combine[cnt - 1].command->order_numb == HERE_DOC
				|| data->combine[cnt - 1].command->order_numb
				== SHELL_REDIRECTION)
			{
				if (investigate_redirections(data, cnt) == ERROR)
					return (ERROR);
			}
			else if (data->combine[cnt].command->order_numb == APOSTROPHE
				|| data->combine[cnt].command->order_numb == QUOTATION_MARK
				|| data->combine[cnt].command->order_numb == STRING)
			{
				if (investigate_quotes(data, cnt) == ERROR)
					return (ERROR);
			}
		}
		cnt++;
	}
	return (EXECUTED);
}

int	parser(t_data *data)
{
	if (*data->line == '\0')
		return (ERROR);
	data->commands_to_process = 0;
	if (parsing_error_handler(data) == ERROR)
		return (ERROR);
	if (set_up_command_struct(data, 0, 0, 0) == ERROR)
		return (ERROR);
	if (find_main_command(data, 0, 0, 0) == ERROR)
		return (ERROR);
	if (retokenize_arrows(data) == ERROR)
		return (ERROR);
	if (check_if_combine_is_valid(data) == ERROR)
		return (ERROR);
	if (crime_scene_investigation(data, 0) == ERROR)
		return (ERROR);
	check_echo_n(data);
	debug_print_t_combine(data);
	return (EXECUTED);
}
