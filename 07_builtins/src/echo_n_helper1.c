/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:10:57 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 20:42:46 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	num_echo(int *numbered, char *str, int quote_state, int cnt)
{
	while (str[cnt] != '\0')
	{
		quote_state = echo_n_quote_state(str, cnt, quote_state);
		if ((str[cnt] == 34 || str[cnt] == 39))
			numbered[cnt] = 1;
		else if (quote_state == 0 && str[cnt] == 'n')
			numbered[cnt] = 2;
		else if (quote_state == 0 && str[cnt] == '-')
			numbered[cnt] = 3;
		else if (quote_state == 0 && is_white_space(str[cnt]) == ADD)
			numbered[cnt] = 0;
		else if (quote_state == 0)
			numbered[cnt] = 4;
		else if (quote_state > 0 && str[cnt] == '-')
			numbered[cnt] = 11;
		else if (quote_state > 0 && str[cnt] == 'n')
			numbered[cnt] = 12;
		else if (quote_state > 0)
			numbered[cnt] = -1;
		cnt++;
	}
}

void	renumber_echo_helper(int *numbered, char *str, size_t cnt)
{
	cnt = 4;
	while (str[cnt] != '\0')
	{
		if (numbered[cnt - 1] == -1)
			numbered[cnt] = -1;
		cnt++;
	}
}

void	renumber_echo2(int *numbered, char *str, size_t cnt)
{
	int	temp;

	temp = 0;
	while (str[cnt] != '\0')
	{
		if (numbered[cnt] == 3 || numbered[cnt] == 11)
		{
			temp = cnt;
			cnt++;
			while (str[cnt] != '\0' && (numbered[cnt] == 2
					|| numbered[cnt] == 1 || numbered[cnt] == 12))
				cnt++;
			if (numbered[cnt] == -1 || numbered[cnt] == 3
				|| numbered[cnt] == 11)
				numbered[temp] = -1;
		}
		else if (numbered[cnt] == 2)
			numbered[cnt] = -1;
		cnt++;
	}
	renumber_echo_helper(numbered, str, cnt);
}

void	renumber_echo1(int *numbered, char *str, size_t cnt)
{
	cnt = 4;
	while (str[cnt] != '\0')
	{
		if (numbered[cnt - 1] == 1 && numbered[cnt -2] == 1
			&& numbered[cnt] != 2 && numbered[cnt] != 3)
			numbered[cnt -2] = -1;
		cnt++;
	}
	cnt = 4;
	renumber_echo_helper(numbered, str, cnt);
	renumber_echo2(numbered, str, 5);
}

void	renumber_echo(int *numbered, char *str, int cnt)
{
	int	temp;

	temp = 0;
	while (str[cnt] != '\0')
	{
		if (numbered[cnt] == 1)
			temp = cnt;
		if (numbered[cnt] == -1)
			numbered[temp] = -1;
		cnt++;
	}
	cnt = 4;
	while (str[cnt] != '\0')
	{
		if (cnt > 4 && (numbered[cnt - 1] == -1 || numbered[cnt] == 4))
			numbered[cnt] = -1;
		cnt++;
	}
	renumber_echo1(numbered, str, cnt);
}
