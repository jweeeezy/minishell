/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:54:42 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/13 18:32:45 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	parser_count_strings(t_data *data, int cnt)
{
	int	tokens;

	tokens = 0;
	while (cnt < data->tokens)
	{
		while (cnt < data->tokens
			&& is_pipe(data->execute[cnt].order_numb) == EXECUTED)
			cnt++;
		if (cnt != 0)
			tokens++;
		if (cnt >= data->tokens)
			return (tokens);
		while (cnt < data->tokens
			&& is_pipe(data->execute[cnt].order_numb) == ADD)
			cnt++;
		tokens++;
		if (cnt >= data->tokens)
			return (tokens);
	}
	return (tokens);
}

void	init_t_combine(t_combine *combine, t_data *data)
{
	int	cnt;

	cnt = 0;
	combine->combined_str = NULL;
	combine->command = NULL;
	while (cnt < data->commands_to_process)
	{
		data->combine[cnt].combined_str = NULL;
		data->combine[cnt].command = NULL;
		cnt++;
	}
}

int	i_hate_norm(t_data *data)
{
	data->commands_to_process = parser_count_strings(data, 0);
	data->combine = malloc(sizeof(t_combine) * (data->commands_to_process + 1));
	if (data->combine == NULL)
		return (ERROR);
	init_t_combine(data->combine, data);
	return (EXECUTED);
}
