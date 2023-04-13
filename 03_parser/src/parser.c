/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/13 14:31:43 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

// int	is_command_mixed(char *str, char *token)
// {

// }

int	is_command(char *str, char *token)
{
	if (ft_strlen(str) == ft_strlen(token)
		&& ft_strnstr(str, token, ft_strlen(str)) != NULL)
		return (ADD);
	return (EXECUTED);
}

int	token_numbers(char *str)
{
	if (is_command(str, "echo") == ADD)
		return (ECHO);
	return (STRING);
}

void	re_number(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		cnt1 = 0;
		while (cnt1 < data->combine[cnt].count_n)
		{
			if (cnt1 < data->combine[cnt].execute[cnt1].order_numb == 0)
				data->combine[cnt].execute[cnt1].order_numb
					= token_numbers(data->combine[cnt].execute[cnt1].order_str);
			cnt1++;
		}
		cnt++;
	}
}

int	parser(t_data *data)
{
	re_number(data);
	return (EXECUTED);
}
