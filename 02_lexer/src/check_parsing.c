/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 13:18:49 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	slasher(t_data *data, int cnt, int q)
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

int	check_parsing(t_data *data)
{
	char	*temp;

	temp = NULL;
	if (slasher(data, 0, 0) == ERROR || data->line == NULL)
	{
		ft_putstr_fd("ERROR\n", 2);
		return (ERROR);
	}
	return (EXECUTED);
}
