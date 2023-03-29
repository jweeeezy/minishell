/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/29 20:48:03 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

static int	merge(t_data *data, int cnt, int cnt1)
{
	int	quote_state;

	quote_state = check_quote_state(data, cnt);
	if (quote_state == APOSTROPHE)
	{
		if (strjoin_with_extra_steps(data, cnt, cnt1) == ERROR)
			return (ERROR);
	}
	else if (quote_state == QUOTATION_MARK)
		return (parser_return_q_m(data, cnt, cnt1));
	else if (quote_state == 0)
		return (parser_return_a(data, cnt, cnt1));
	return (EXECUTED);
}

static int	set_up_command_struct(t_data *data, int cnt, int cnt1, int switcher)
{
	int	skip;

	cnt = skip_white_spaces(data, 0);
	switcher = is_pipe(data->execute[cnt].order_numb);
	if (i_hate_norm(data) == ERROR)
		return (ERROR);
	while (cnt < data->tokens)
	{
		if (is_pipe(data->execute[cnt].order_numb) == switcher)
		{
			skip = merge(data, cnt, cnt1);
			if (skip == ERROR)
				return (ERROR);
			else if (skip == ADD)
				cnt++;
			cnt++;
		}
		else
		{
			switcher = is_pipe(data->execute[cnt].order_numb);
			cnt1++;
		}
	}
	return (EXECUTED);
}

int	check_if_combine_is_valid(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].combined_str == NULL)
		{
			data->combine[cnt].combined_str = malloc(sizeof(char) * 2);
			if (data->combine[cnt].combined_str == NULL)
				return (ERROR);
			*(data->combine[cnt].combined_str) = ' ';
			*(data->combine[cnt].combined_str + 1) = '\0';
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
	if (check_if_combine_is_valid(data) == ERROR)
		return (ERROR);
	check_echo_n(data);
	debug_print_t_combine(data);
	return (EXECUTED);
}
