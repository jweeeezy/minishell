/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 15:04:38 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	quoter(t_data *data, int cnt, int q)
{
	char	*temp;

	temp = NULL;
	while (data->line[cnt] != '\0')
	{
		q = q_state(data->line, cnt, q);
		cnt++;
	}
	if (q > 0)
		return (ERROR);
	return (EXECUTED);
}

int	piper(t_data *data)
{
	size_t	cnt;

	cnt = 0;
	while (data->line[cnt] != '\0')
	{
		if (data->line[0] == '|')
			return (ERROR);
		if (cnt == ft_strlen(data->line) - 1)
		{
			if (data->line[cnt] == '|')
				return (ERROR);
		}
		cnt++;
	}
	return (EXECUTED);
}

int	check_parsing(t_data *data)
{
	char	*temp;

	temp = NULL;
	if (quoter(data, 0, 0) == ERROR)
	{
		ft_putstr_fd("ERROR\n", 2);
		return (ERROR);
	}
	if (piper(data) == ERROR)
	{
		ft_putstr_fd("ERROR\n", 2);
		return (ERROR);
	}
	return (EXECUTED);
}
