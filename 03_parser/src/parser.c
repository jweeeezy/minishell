/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/12 10:21:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

static int	merge(t_data *data, int cnt, int cnt1)
{
	data->combine[cnt1].combined_str
		= ft_strjoin2(data->combine[cnt1].combined_str,
			data->execute[cnt].order_str, 0, 0);
	if (data->combine[cnt1].combined_str == NULL)
		return (ERROR);
	printf("%s\n", data->combine[cnt1].combined_str);
	return (EXECUTED);
}

static int	count_strings(t_data *data, int cnt)
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

static int	skip_white_spaces(t_data *data, int cnt)
{
	while (cnt < data->tokens && data->execute[cnt].order_numb == WHITE)
		cnt++;
	return (cnt);
}

static int	set_up_command_struct(t_data *data, int cnt, int cnt1, int switcher)
{
	cnt = skip_white_spaces(data, 0);
	switcher = is_pipe(data->execute[cnt].order_numb);
	data->commands_to_process = count_strings(data, 0);
	data->combine = malloc(sizeof(t_combine) * (data->commands_to_process + 1));
	while (cnt < data->tokens)
	{
		if (is_pipe(data->execute[cnt].order_numb) == switcher)
		{
			if (merge(data, cnt, cnt1) == ERROR)
				return (ERROR);
			cnt++;
		}
		else
		{
			switcher = is_pipe(data->execute[cnt].order_numb);
			cnt1++;
		}
	}
	return (EXECUTED);
}

int	parser(t_data *data)
{
	printf("I am here\n");
	if (parsing_error_handler(data) == ERROR)
		return (EXECUTED);
	if (set_up_command_struct(data, 0, 0, 0) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
