/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:18:28 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/11 20:08:00 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

void	determine_quote_state3(char *str, int *numb, int *numb1, int last)
{
	int	cnt;

	cnt = 0;
	while (str[cnt] != '\0')
	{
		if (numb[cnt] == 60 || numb[cnt] == 62)
		{
			last = numb[cnt];
			while (str[cnt] != '\0' && last == numb[cnt])
				cnt++;
			while (str[cnt] != '\0' && numb[cnt] == 1)
			{
				numb1[cnt] = numb1[cnt] - 1;
				cnt++;
			}
			while (str[cnt] != '\0' && (numb[cnt] == 0
					|| numb[cnt] == 34 || numb[cnt] == 39))
			{
				numb1[cnt] = numb1[cnt] - 1;
				cnt++;
			}
		}
		else
			cnt++;
	}
}

void	determine_quote_state2(char *str, int *numb1)
{
	int	cnt;

	cnt = 0;
	if (str[cnt] != '\0' && numb1[cnt] == 0)
		return ;
	while (str[cnt] != '\0')
	{
		numb1[cnt] = numb1[cnt] - 1;
		cnt++;
	}
}

void	determine_quote_state1(char *str, int *numb, t_var	*var, int *numb1)
{
	if (str[var->cnt] != '\0')
		var->last = numb[var->cnt];
	while (str[var->cnt] != '\0')
	{
		if (numb[var->cnt] >= 60)
		{
			var->cnt1++;
			var->last = numb[var->cnt];
			while (str[var->cnt] != '\0' && var->last == numb[var->cnt])
			{
				numb1[var->cnt] = var->cnt1;
				var->cnt++;
			}
			var->cnt1++;
		}
		else
		{
			numb1[var->cnt] = var->cnt1;
			var->cnt++;
		}
	}
}

void	determine_quote_state(char *str, int cnt, int *numb, int *numb1)
{
	int		quote_state;
	t_var	var;

	var.last = 0;
	var.cnt1 = 0;
	var.cnt = 0;
	quote_state = 0;
	while (str[cnt] != '\0')
	{
		quote_state = q_state(str, cnt, quote_state);
		numb[cnt] = quote_state;
		if (quote_state == 0 && (str[cnt] == 34 || str[cnt] == 39))
			numb[cnt] = str[cnt];
		if ((str[cnt] == '<' || str[cnt] == '>' || str[cnt] == '|')
			&& quote_state < 30)
			numb[cnt] = str[cnt];
		if (numb[cnt] == 0)
			numb[cnt] = is_white_space(str[cnt]);
		cnt++;
	}
	determine_quote_state1(str, numb, &var, numb1);
	determine_quote_state2(str, numb1);
	determine_quote_state3(str, numb, numb1, 0);
}
