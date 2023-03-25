/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:42:00 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/25 15:31:36 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

void	check_echo_n(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		cnt1 = data->combine[cnt].command->number;
		if (cnt1 + 1 < data->tokens)
				cnt1++;
		if (data->combine[cnt].command->order_numb == ECHO)
		{
			while (is_n(data->execute[cnt1].order_str) == ADD
				|| data->execute[cnt1].order_numb == WHITE
				|| data->execute[cnt1].order_numb == DOLLA)
			{
				if (cnt1 + 1 < data->tokens && execute[cnt1].order_numb == DOLLA)
				{
					
				}
				if (is_n(data->execute[cnt1].order_str) == ADD)
					data->combine[cnt].count_n++;
				cnt1++;
			}
			if (data->combine[cnt].count_n > 0)
				data->combine[cnt].command->order_numb = ECHO_N;
		}
		cnt++;
	}
}
