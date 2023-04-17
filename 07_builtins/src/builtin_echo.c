/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/16 10:28:42 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	print_echo(int n, int cnt1, t_combine str)
{
	if (n == 0)
		printf("%s\n", str.combined_str + cnt1);
	else
		printf("%s", str.combined_str + cnt1);
}

void	echo(t_combine str, int n, int cnt2, int is_echo_skiped)
{
	int	cnt1;

	cnt1 = 1;
	while (cnt2 < str.count_n)
	{
		if (str.command[cnt2].order_numb == ECHO && is_echo_skiped == 0)
		{
			is_echo_skiped = 1;
			cnt1 = cnt1 + ft_strlen(str.command[cnt2].order_str);
		}
		else if (str.command[cnt2].order_numb == WHITE)
		{
		}
		else if (str.command[cnt2].order_numb == N
			|| str.command[cnt2].order_numb == WIERD_N)
		{
			cnt1 = cnt1 + ft_strlen(str.command[cnt2].order_str) + 1;
			n = 1;
		}
		else
			break ;
		cnt2++;
	}
	print_echo(n, cnt1, str);
}

void	wierd_echo(t_combine str, int n, int cnt2, int is_echo_skiped)
{
	int	cnt1;

	cnt1 = 1;
	while (cnt2 < str.count_n)
	{
		if (str.command[cnt2].order_numb == REJECTED_ECHO
			&& is_echo_skiped == 0)
		{
			is_echo_skiped = 1;
			cnt1 = cnt1 + ft_strlen(str.command[cnt2].order_str);
		}
		else if (str.command[cnt2].order_numb == WHITE)
		{
		}
		else if (str.command[cnt2].order_numb == N)
		{
			cnt1 = cnt1 + ft_strlen(str.command[cnt2].order_str) + 1;
			n = 1;
			break ;
		}
		else
			break ;
		cnt2++;
	}
	print_echo(n, cnt1, str);
}
