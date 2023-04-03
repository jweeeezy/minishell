/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 14:38:39 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"    

int	count_split(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	split_free(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
	{
		free(split[cnt]);
		cnt++;
	}
	free(split);
}

int	q_state(char *str, int cnt, int quote_state)
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
