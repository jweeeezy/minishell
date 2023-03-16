/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:02:54 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/15 11:45:03 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	quote_check(t_data *data)
{
	int	cnt;
	int	quote_check;
	int	quote_id;

	cnt = 0;
	quote_check = 0;
	quote_id = 0;
	while (cnt < data->tokens)
	{
		if ((data->execute[cnt].order_numb == 3
				|| data->execute[cnt].order_numb == 4) && quote_check == 0)
		{
			quote_check = 1;
			quote_id = data->execute[cnt].order_numb;
		}
		else if (quote_id == data->execute[cnt].order_numb)
		{
			quote_check = 0;
			quote_id = 0;
		}
		cnt++;
	}
	return (quote_check);
}

int	parsing_error_handler(t_data *data)
{
	if (quote_check(data) == 1)
	{
		printf("Quote BDU>\n");
		return (ERROR);
	}
	return (EXECUTED);
}

int	check_quote_state(t_data *data, int cnt)
{
	int	quote_check;
	int	quote_id;
	int	cnt1;

	cnt1 = 0;
	quote_check = 0;
	quote_id = 0;
	while (cnt1 < cnt && cnt1 < data->tokens)
	{
		if ((data->execute[cnt1].order_numb == 3
				|| data->execute[cnt1].order_numb == 4) && quote_check == 0)
		{
			quote_check = 1;
			quote_id = data->execute[cnt1].order_numb;
		}
		else if (quote_id == data->execute[cnt1].order_numb)
		{
			quote_check = 0;
			quote_id = 0;
		}
		cnt1++;
	}
	if (quote_id == data->execute[cnt1].order_numb)
		quote_id = 0;
	return (quote_id);
}

int	strjoin_with_extra_steps(t_data *data, int cnt, int cnt1)
{
	data->combine[cnt1].combined_str
		= ft_strjoin2(data->combine[cnt1].combined_str,
			data->execute[cnt].order_str, 0, 0);
	if (data->combine[cnt1].combined_str == NULL)
		return (ERROR);
	return (EXECUTED);
}
