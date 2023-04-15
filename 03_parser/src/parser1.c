/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:33:51 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/15 10:15:27 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

void	main_command(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].count_n > 0
			&& data->combine[cnt].execute[0].order_numb != WHITE)
			data->combine[cnt].command = &data->combine[cnt].execute[0];
		else if (data->combine[cnt].count_n > 1
			&& data->combine[cnt].execute[1].order_numb != WHITE)
			data->combine[cnt].command = &data->combine[cnt].execute[1];
		else if (data->combine[cnt].count_n > 0)
			data->combine[cnt].command = &data->combine[cnt].execute[0];
		cnt++;
	}
}

int	recheck_the_combined_str(t_data *data, int cnt)
{
	if (data->combine[cnt].combined_str == NULL)
	{
		data->combine[cnt].combined_str = ft_strdup("");
		if (data->combine[cnt].combined_str == NULL)
			return (ERROR);
	}
	return (EXECUTED);
}

int	recombine_str(t_data *data, int cnt, int cnt1, char *temp)
{
	while (cnt < data->commands_to_process)
	{
		temp = NULL;
		cnt1 = 0;
		while (data->combine != NULL && cnt1 < data->combine[cnt].count_n)
		{
			if (data->combine[cnt].execute[cnt1].order_numb != WHITE)
			{
				temp = ft_strjoin2(temp,
						data->combine[cnt].execute[cnt1].order_str, 0, 0);
				temp = ft_charjoin(temp, ' ', 0, 0);
				if (temp == NULL)
					return (ERROR);
			}
			cnt1++;
		}
		free(data->combine[cnt].combined_str);
		data->combine[cnt].combined_str = ft_strdup(temp);
		if (temp != NULL)
			free(temp);
		if (recheck_the_combined_str(data, cnt) == ERROR)
			return (ERROR);
		cnt++;
	}
	return (EXECUTED);
}
