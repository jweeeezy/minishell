/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:54:42 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/13 09:57:26 by kvebers          ###   ########.fr       */
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

void	init_t_combine(t_combine *combine)
{
	combine->combined_str = NULL;
	combine->execute_order = 0;
	combine->command = NULL;
}

int	i_hate_norm(t_data *data)
{
	data->commands_to_process = parser_count_strings(data, 0);
	data->combine = malloc(sizeof(t_combine) * (data->commands_to_process + 1));
	if (data->combine == NULL)
		return (ERROR);
	init_t_combine(data->combine);
	return (EXECUTED);
}
