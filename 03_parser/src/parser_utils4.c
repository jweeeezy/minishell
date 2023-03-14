/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:02:58 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/14 16:52:56 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	check_space_state(t_data *data, int cnt)
{
	if (data->execute[cnt].order_numb == APOSTROPHE
		|| data->execute[cnt].order_numb == QUOTATION_MARK)
		return (EXECUTED);
	if (cnt - 1 >= 0 && data->execute[cnt - 1].order_numb == WHITE
		&& data->execute[cnt].order_numb == WHITE)
		return (EXECUTED);
	if (cnt - 1 >= 0 && is_pipe(data->execute[cnt - 1].order_numb)
		&& data->execute[cnt].order_numb == WHITE)
		return (EXECUTED);
	if (data->execute[cnt].order_numb == DOLLA)
		return (DOLLA);
	return (ADD);
}

int	no_quote(t_data *data, int cnt, int cnt1)
{
	if (check_space_state(data, cnt) == ADD)
	{
		if (strjoin_with_extra_steps(data, cnt, cnt1) == ERROR)
			return (ERROR);
	}
	else if (check_space_state(data, cnt) == DOLLA)
	{
		if (dolla_handler(data, cnt, cnt1) == ERROR)
			return (ERROR);
		return (ADD);
	}
	return (EXECUTED);
}


static void	find_last_pipe(t_data *data)
{
	int	cnt;
	int	temp;

	cnt = 0;
	temp = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].command->order_numb == PIPE)
			temp = cnt;
		cnt++;
	}
	if (data->combine->combined_str != NULL
		&& data->combine[temp].command->order_numb == PIPE)
		data->combine[temp].command->order_numb = PIPE * 10;
}

static int	check_the_variables(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].command->order_numb == DOLLA
			&& data->combine[cnt].combined_str != NULL)
		{
			if (recheck_the_main_command(data, cnt) == ERROR)
				return (ERROR);
		}	
		cnt++;
	}
	return (EXECUTED);
}

int	find_main_command(t_data *data, int cnt, int cnt1, int switcher)
{
	switcher = is_pipe(data->execute[cnt].order_numb);
	while (cnt < data->tokens)
	{
		if (is_pipe(data->execute[cnt].order_numb) == switcher)
		{
			if (data->combine[cnt1].command == NULL
				&& data->execute[cnt].order_numb > WHITE)
				data->combine[cnt1].command = &data->execute[cnt];
				cnt++;
		}
		else
		{
			switcher = is_pipe(data->execute[cnt].order_numb);
			cnt1++;
		}
	}
	find_last_pipe(data);
	if (check_the_variables(data) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
