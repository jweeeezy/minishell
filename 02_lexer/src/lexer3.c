/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:34:00 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 22:15:20 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

int	tokens(t_data *data, int *numb1, int cnt1)
{
	int	cnt;
	int	last_value;
	int	cnt2;

	cnt = 0;
	last_value = -1;
	cnt2 = -1;
	while (data->combine[cnt1].combined_str[cnt] != '\0')
	{
		if (last_value != numb1[cnt])
		{
			printf("%c", data->combine[cnt1].combined_str[cnt]);
			last_value = numb1[cnt];
			cnt2++;
		}
		data->combine[cnt1].order_str[cnt2]
			= ft_charjoin(data->combine[cnt1].order_str[cnt2],
				data->combine[cnt1].combined_str[cnt], 0, 0);
		if (data->combine[cnt1].order_str)
		cnt++;
	}
	return (EXECUTED);
}

int	create_tks(t_data *data, int *numb1, int cnt1)
{
	data->combine[cnt1].order_str
		= malloc(data->combine[cnt1].tks * sizeof(char *));
	if (data->combine[cnt1].order_str == NULL)
		return (ERROR);
	init_tokens(data, cnt1);
	if (tokens(data, numb1, cnt1) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
