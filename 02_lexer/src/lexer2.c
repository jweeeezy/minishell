/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:41:33 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 14:22:06 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

int	estimate_tokens(t_data *data, int cnt, int cnt1, int cnt2)
{
	int	sw;
	int	quote;

	quote = 0;
	if (data->combine[cnt].combined_str == NULL)
		return (1);
	sw = is_white_space(data->combine[cnt].combined_str[cnt1]);
	while (data->combine[cnt].combined_str[cnt1] != '\0')
	{
		quote = q_state(data->combine[cnt].combined_str, cnt1, quote);
		if (sw != is_white_space(data->combine[cnt].combined_str[cnt1]))
		{
			if (quote < 30 || data->combine[cnt].combined_str[cnt1] == 34
				|| data->combine[cnt].combined_str[cnt1] == 39)
			{
				sw = is_white_space(data->combine[cnt].combined_str[cnt1]);
				cnt2++;
			}
		}
		cnt1++;
	}
	return (cnt2 + 1);
}

int	init_ex_tokens(t_data *data, int cnt, int cnt1, int cnt2)
{
	int	sw;
	int	quote;

	quote = 0;
	sw = is_white_space(data->combine[cnt].combined_str[cnt1]);
	while (data->combine[cnt].combined_str[cnt1] != '\0')
	{
		quote = q_state(data->combine[cnt].combined_str, cnt1, quote);
		if (sw != is_white_space(data->combine[cnt].combined_str[cnt1]))
		{
			if (quote < 30 || data->combine[cnt].combined_str[cnt1] == 34
				|| data->combine[cnt].combined_str[cnt1] == 39)
			{
				sw = is_white_space(data->combine[cnt].combined_str[cnt1]);
				cnt2++;
			}
		}
		data->combine[cnt].execute[cnt2].order_str
			= ft_charjoin(data->combine[cnt].execute[cnt2].order_str,
				data->combine[cnt].combined_str[cnt1], 0, 0);
		if (data->combine[cnt].execute[cnt2].order_str == NULL)
			return (ERROR);
		cnt1++;
	}
	return (EXECUTED);
}

void	init_tokens(t_data *data, int cnt)
{
	int	cnt1;

	cnt1 = 0;
	while (cnt1 < data->combine[cnt].count_n)
	{
		data->combine[cnt].execute[cnt1].order_str = NULL;
		data->combine[cnt].execute[cnt1].order_numb = 0;
		if (data->combine[cnt].count_n > 0)
			data->combine[cnt].execute[0].order_numb
				= token_numbers_helper(data->combine[cnt].combined_str);
		cnt1++;
	}
}

int	create_tokens(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (expand_line(data, cnt, 0) == ERROR)
			return (ERROR);
		data->combine[cnt].count_n = estimate_tokens(data, cnt, 0, 0);
		data->combine[cnt].execute = malloc(sizeof(t_execute)
				* data->combine[cnt].count_n);
		if (data->combine[cnt].execute == NULL)
			return (ERROR);
		init_tokens(data, cnt);
		if (remove_null(data, cnt) == ERROR)
			return (ERROR);
		if (init_ex_tokens(data, cnt, 0, 0) == ERROR)
			return (ERROR);
		if (remove_whitespaces(data, cnt) == ERROR
			|| remove_quotes(data, cnt, 0) == ERROR)
			return (ERROR);
		cnt++;
	}
	return (EXECUTED);
}
