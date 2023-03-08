/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/08 14:43:41 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	execute_command(t_data *data, int cnt, int is_piped)
{
	if (is_piped != ERROR)
	{
		if (data->execute[cnt].order_numb == ECHO)
			echo(data, cnt);
	}
}

int	pipe_error_handler(t_data *data, int cnt)
{
	if (is_pipe(data->execute[cnt].order_numb) == ADD)
			cnt++;
	if (is_pipe(data->execute[cnt].order_numb) == ADD)
			cnt++;
	if (is_pipe(data->execute[cnt].order_numb) == ADD)
	{
			data->execute[cnt].order_numb = ERROR;
			data->execute[cnt - 1].order_numb = ERROR;
			data->execute[cnt - 2].order_numb = ERROR;
			cnt++;
	}
	return (cnt);
}

int	parser(t_data *data)
{
	int	cnt;
	int	is_piped;

	is_piped = 0;
	cnt = 0;
	while (cnt < data->tokens)
	{
		while (data->execute[cnt].order_numb == WHITE && cnt < data->tokens)
			cnt++;
		if (cnt < data->tokens)
			execute_command(data, cnt, is_piped);
		while (is_pipe(data->execute[cnt].order_numb) == EXECUTED
			&& cnt < data->tokens)
			cnt++;
		cnt = pipe_error_handler(data, cnt);
		if (cnt != data->tokens)
			is_piped = data->execute[cnt - 1].order_numb;
	}
	printf("%s", data->string);
	return (EXECUTED);
}
