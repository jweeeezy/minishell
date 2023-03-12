/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/12 20:37:12 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

static int	merge(t_data *data, int cnt, int cnt1)
{
	int	quote_state;
	int	state;

	quote_state = check_quote_state(data, cnt);
	if (quote_state == APOSTROPHE)
	{
		if (strjoin_with_extra_steps(data, cnt, cnt1) == ERROR)
			return (ERROR);
	}
	else if (quote_state == QUOTATION_MARK)
	{
		state = handle_quotes(data, cnt, cnt1);
		if (state == ERROR)
			return (ERROR);
		else if (state == ADD)
			return (ADD);
	}
	else if (quote_state == 0)
	{
	}
	return (EXECUTED);
}

static int	count_strings(t_data *data, int cnt)
{
	int	tokens;

	tokens = 0;
	while (cnt < data->tokens)
	{
		while (cnt < data->tokens
			&& is_pipe(data->execute[cnt].order_numb) == EXECUTED)
			cnt++;
		if (cnt != 0)
			tokens++;
		if (cnt >= data->tokens)
			return (tokens);
		while (cnt < data->tokens
			&& is_pipe(data->execute[cnt].order_numb) == ADD)
			cnt++;
		tokens++;
		if (cnt >= data->tokens)
			return (tokens);
	}
	return (tokens);
}

static void	init_t_combine(t_combine *combine)
{
	combine->combined_str = NULL;
	combine->execute_order = 0;
	combine->command = NULL;
}

static int	i_hate_norm(t_data *data)
{
	data->commands_to_process = count_strings(data, 0);
	data->combine = malloc(sizeof(t_combine) * (data->commands_to_process + 1));
	if (data->combine == NULL)
		return (ERROR);
	init_t_combine(data->combine);
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
			printf("%s\n", data->combine[cnt1].combined_str);
			cnt1++;
		}
	}
	printf("%s\n", data->combine[cnt1].combined_str);
	return (EXECUTED);
}

int	parser(t_data *data)
{
	data->commands_to_process = 0;
	if (parsing_error_handler(data) == ERROR)
		return (EXECUTED);
	if (set_up_command_struct(data, 0, 0, 0) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
