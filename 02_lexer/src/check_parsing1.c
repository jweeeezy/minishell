/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:58:09 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/24 11:05:50 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	check_wierd(t_data *data, char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt + 1] == '\0')
			return (EXECUTED);
		if (str[cnt] == '<' || str[cnt] == '>' || str[cnt] == '|')
		{
			if (str[cnt + 1] == '<' || str[cnt + 1] == '>'
				|| str[cnt + 1] == '|')
			{
				if (str[cnt] != str[cnt + 1])
				{
					ft_putstr_fd("ERROR Wierd Pies and stuff", 2);
					data->exit_status = 127;
					return (ERROR);
				}
			}
		}
		cnt++;
	}
    return (EXECUTED);
}
