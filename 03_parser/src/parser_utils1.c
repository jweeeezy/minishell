/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:02:54 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/11 10:05:42 by kvebers          ###   ########.fr       */
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
		printf("Quote>\n");
		return (ERROR);
	}
	return (EXECUTED);
}