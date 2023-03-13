/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/13 10:13:11 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	execute_command(t_data *data, int cnt, int is_piped)
{
	if (is_piped != ERROR)
	{
		if (data->execute[cnt].order_numb == ECHO)
			cnt = echo(data, cnt + 1);
		else
		{
			if (executor_main(data) == ERROR)
				return (ERROR);
		}
	}
	return (cnt);
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

int	quote_check(t_data *data)
{
	int	cnt;
	int	quote_check;
	int	quote_id;

	cnt = 0;
	quote_check = 0;
	quote_id = 0;
	while (cnt < data->tokens)
	{
		if ((data->execute[cnt].order_numb == 3
				|| data->execute[cnt].order_numb == 4) && quote_check == 0)
		{
			quote_check = 1;
			quote_id = data->execute[cnt].order_numb;
		}
		else if (quote_id == data->execute[cnt].order_numb)
		{
			quote_check = 0;
			quote_id = 0;
		}
		cnt++;
	}
	return (quote_check);
}

static int	parsing_error_handler(t_data *data)
{
	if (quote_check(data) == 1)
	{
		printf("Quote>\n");
		return (ERROR);
	}
	return (EXECUTED);
}

int	parser(t_data *data)
{
	int	cnt;
	int	is_piped;

	is_piped = 0;
	cnt = 0;
	if (parsing_error_handler(data) == ERROR)
		return (EXECUTED);

	execute_command(data, cnt, is_piped);
	while (cnt < data->tokens)
	{
		while (data->execute[cnt].order_numb == WHITE && cnt < data->tokens)
			cnt++;
		//if (cnt < data->tokens)
//			cnt = execute_command(data, cnt, is_piped);
		while (is_pipe(data->execute[cnt].order_numb) == EXECUTED
			&& cnt < data->tokens)
			cnt++;
		cnt = pipe_error_handler(data, cnt);
		if (cnt != data->tokens)
			is_piped = data->execute[cnt - 1].order_numb;
	}
	if (data->string != NULL)
		printf("%s\n", data->string);
	return (EXECUTED);
}
