/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:11:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/22 10:24:40 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	error_conseq_pipes(t_data *data, int cnt, int last_command, int q_o)
{
	while (cnt < data->tokens && data->execute[cnt].order_numb == WHITE)
		cnt++;
	if (data->execute[cnt].order_numb == PIPE)
		return (ERROR);
	while (cnt < data->tokens)
	{
		if (q_o == 0 && (data->execute[cnt].order_numb == QUOTATION_MARK
				|| data->execute[cnt].order_numb == APOSTROPHE))
			q_o = data->execute[cnt].order_numb;
		else if (q_o == data->execute[cnt].order_numb)
			q_o = 0;
		if (cnt + 1 < data->tokens && data->execute[cnt].order_numb == PIPE
			&& data->execute[cnt + 1].order_numb == PIPE && q_o == 0)
			return (ERROR);
		if (data->execute[cnt].order_numb != WHITE)
			last_command = data->execute[cnt].order_numb;
		cnt++;
	}
	if (last_command == PIPE)
		return (ERROR);
	return (EXECUTED);
}

static int	error_conseq_seps(t_data *data, int cnt, int q_o, int last_command)
{
	while (cnt < data->tokens)
	{
		if (q_o == 0 && (data->execute[cnt].order_numb == QUOTATION_MARK
				|| data->execute[cnt].order_numb == APOSTROPHE))
			q_o = data->execute[cnt].order_numb;
		else if (q_o == data->execute[cnt].order_numb)
			q_o = 0;
		if (cnt + 1 < data->tokens
			&& is_micro_pipe(data->execute[cnt].order_numb)
			&& is_micro_pipe(data->execute[cnt + 1].order_numb) && q_o == 0)
			return (ERROR);
		if (data->execute[cnt].order_numb != WHITE)
			last_command = data->execute[cnt].order_numb;
		cnt++;
	}
	if (is_micro_pipe(last_command) == ADD)
		return (ERROR);
	return (EXECUTED);
}

static int	error_3_sep(t_data *data, int cnt, int q_o, int last_command)
{
	while (cnt < data->tokens)
	{
		if (q_o == 0 && (data->execute[cnt].order_numb == QUOTATION_MARK
				|| data->execute[cnt].order_numb == APOSTROPHE))
			q_o = data->execute[cnt].order_numb;
		else if (q_o == data->execute[cnt].order_numb)
			q_o = 0;
		if (cnt + 2 < data->tokens
			&& is_pipe(data->execute[cnt].order_numb)
			&& is_pipe(data->execute[cnt + 1].order_numb) && q_o == 0
			&& is_pipe(data->execute[cnt + 2].order_numb) && q_o == 0)
			return (ERROR);
		if (data->execute[cnt].order_numb != WHITE)
			last_command = data->execute[cnt].order_numb;
		cnt++;
	}
	if (is_micro_pipe(last_command) == ADD)
		return (ERROR);
	return (EXECUTED);
}

static int	pipe_error_handeler(t_data *data)
{
	if (error_conseq_pipes(data, 0, 0, 0) == ERROR)
	{
		printf("ERROR: This ain't elder wand this is |PIPE|\n");
		return (ERROR);
	}
	else if (error_conseq_seps(data, 0, 0, 0) == ERROR)
	{
		printf("ERROR: You have some sketcy stuff going out there with <>|\n");
		return (ERROR);
	}
	else if (error_3_sep(data, 0, 0, 0) == ERROR)
	{
		printf("ERROR: Bozo, BOZO! You have too many of these bad boys <>|\n");
		return (ERROR);
	}
	return (EXECUTED);
}

int	token_error_handeler(t_data *data)
{
	if (pipe_error_handeler(data) == ERROR)
		return (ERROR);
	if (syntax_errors(data) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
