/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:11:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/20 16:12:38 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	error_consequatives_pipes(t_data *data, int cnt, int last_command, int q_o)
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

int	error_conseq_seperators(t_data *data, int cnt, int q_o, int last_command)
{
	while (cnt < data->tokens)
	{
		if (q_o == 0 && (data->execute[cnt].order_numb == QUOTATION_MARK
				|| data->execute[cnt].order_numb == APOSTROPHE))
			q_o = data->execute[cnt].order_numb;
		else if (q_o == data->execute[cnt].order_numb)
			q_o = 0;
		if (cnt + 1 < data->tokens && data->execute[cnt].order_numb
			&& data->execute[cnt + 1].order_numb && q_o == 0)
			return (ERROR);
		if (last_command != WHITE)
			last_command = data->execute[cnt + 1].order_numb;
		cnt++;
	}
	return (EXECUTED);
}

int	pipe_error_handeler(t_data *data)
{
	if (error_consequatives_pipes(data, 0, 0, 0) == ERROR)
	{
		printf("ERROR: Syntax error near |\n");
		return (ERROR);
	}
	return (EXECUTED);
}

int	token_error_handeler(t_data *data)
{
	if (pipe_error_handeler(data) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
