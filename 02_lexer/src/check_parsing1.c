/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:58:09 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/25 16:43:28 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	check_wierd1(t_data *data, char *str)
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
					ft_putstr_fd("ERROR Wierd Pies and stuff\n", 2);
					data->exit_status = 127;
					return (ERROR);
				}
			}
		}
		cnt++;
	}
	return (EXECUTED);
}

int	check_wierd(t_data *data)
{
	char	*str;
	int		cnt;

	cnt = 0;
	str = NULL;
	while (data->line[cnt] != '\0')
	{
		if (is_white_space(data->line[cnt]) == 0)
			str = ft_charjoin(str, data->line[cnt], 0, 0);
		cnt++;
	}
	if (str != NULL)
		if (check_wierd1(data, str) == ERROR)
			return (free(str), ERROR);
	if (str != NULL)
		free(str);
	return (EXECUTED);
}
