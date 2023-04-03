/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:18:28 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 22:53:42 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

void	determin_helper(char *str, int *numb, int *numb1, t_var *var)
{
	if (var->blob_state == 0 && (var->last == '<' || var->last == '>'))
	{
		while (str[var->cnt] != '\0' && numb[var->cnt] == 1)
		{
			numb1[var->cnt] = var->cnt1;
			var->cnt++;
		}
		while (str[var->cnt] != '\0' && (numb[var->cnt] == 0
				|| numb[var->cnt] == 34 || numb[var->cnt] == 39))
		{
			numb1[var->cnt] = var->cnt1;
			var->cnt++;
		}
		var->blob_state = 1;
	}
	else if (var->blob_state == 0 && var->last == '|')
		var->blob_state = 1;
}

void	determine_quote_state1(char *str, int *numb, t_var *var, int *numb1)
{
	while (str[var->cnt] != '\0')
	{
		if (str[var->cnt] == '<' || str[var->cnt] == '>'
			|| str[var->cnt] == '|')
		{
			if (var->cnt1 != 0)
				var->cnt1++;
			var->last = str[var->cnt];
			var->blob_state = 0;
			while (str[var->cnt] != '\0' && numb[var->cnt] == var->last)
			{
				numb1[var->cnt] = var->cnt1;
				var->cnt++;
			}
			determin_helper(str, numb, numb1, var);
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
	var.blob_state = 0;
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
	if (DEBUG)
		print_numberator(str, numb, numb1);
}
