/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:29:32 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/29 14:35:19 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	quoted_heredoc(char *str)
{
	int	cnt;

	cnt = 2;
	while (str[cnt] != '\0')
	{
		if (is_white_space(str[cnt]) == ADD)
			cnt++;
		else if (str[cnt] == 34)
			return (ADD);
		else
			return (EXECUTED);
	}
	return (EXECUTED);
}

void	fix_env_flags(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].command->order_numb == ENV
			&& data->combine[cnt].count_n > 2)
				data->combine[cnt].command->order_numb = STRING;
		cnt++;
	}
}
