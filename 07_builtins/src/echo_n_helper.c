/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:49:40 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/30 17:45:11 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

char	*ft_charjoin(char *temp, char c, size_t cnt1, size_t cnt2)
{
	char	*new_temp;

	if (temp == NULL)
	{
		temp = malloc(sizeof(char));
		*temp = '\0';
	}
	if (temp == NULL)
		return (NULL);
	new_temp = malloc((ft_strlen(temp) + 2) * sizeof(char));
	if (new_temp == NULL)
		return (NULL);
	while (*(temp + cnt1) != '\0')
	{
		*(new_temp + cnt1) = *(temp + cnt1);
		cnt1++;
	}
	*(new_temp + cnt1 + cnt2) = c;
	cnt2++;
	*(new_temp + cnt1 + cnt2) = '\0';
	return (free(temp), new_temp);
}

int	echo_n_quote_state(char *str, int cnt, int quote_state)
{
	if (str[cnt] == 34 && quote_state == 0)
		quote_state = 34;
	else if (str[cnt] == 39 && quote_state == 0)
		quote_state = 39;
	else if (str[cnt] == 39 && quote_state == 39)
		quote_state = 0;
	else if (str[cnt] == 34 && quote_state == 34)
		quote_state = 0;
	return (quote_state);
}

char	*echo_n_helper(t_data *data, int cnt, char *comb)
{
	char	*dolla;

	while (cnt < data->tokens
		&& is_pipe(data->execute[cnt].order_numb) == EXECUTED)
	{
		if (cnt + 1 < data->tokens && data->execute[cnt].order_numb == DOLLA
			&& data->execute[cnt + 1].order_numb != WHITE
			&& check_quote_state(data, cnt) != 3)
		{
			cnt++;
			dolla = NULL;
			dolla = search_needle(data, data->execute[cnt].order_str);
			if (dolla != NULL)
			{
				dolla = dolla + ft_strlen(data->execute[cnt].order_str) + 1;
				comb = ft_strjoin2(comb, dolla, 0, 0);
			}
		}
		else
			comb = ft_strjoin2(comb, data->execute[cnt].order_str, 0, 0);
		if (comb == NULL)
			return (NULL);
		cnt++;
	}
	return (comb);
}

char	*echo_merge(char *str, size_t cnt, int quote_state)
{
	char	c;
	char	*merge;

	cnt = 0;
	quote_state = 0;
	merge = NULL;
	while (str[cnt] != '\0')
	{
		quote_state = echo_n_quote_state(str, cnt, quote_state);
		if (quote_state == 0 && (str[cnt] == 34 || str[cnt] == 39)
			&& cnt + 1 < ft_strlen(str) && (str[cnt + 1] == 34
				|| str[cnt + 1] == 39))
		{
			cnt++;
			quote_state = echo_n_quote_state(str, cnt, quote_state);
		}
		else
		{
			c = str[cnt];
			merge = ft_charjoin(merge, c, 0, 0);
		}
		cnt++;
	}
	return (free(str), merge);
}
