/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:32:37 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/22 10:07:49 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	last_pipe(t_data *data)
{
	int	cnt;
	int	last_command;

	cnt = 0;
	while (cnt < data->tokens)
	{
		if (data->execute[cnt].order_numb != WHITE)
			last_command = data->execute[cnt].order_numb;
		cnt++;
	}
	if (last_command == PIPE || last_command == FILE_TO_COMMAND
		|| last_command == COMMAND_TO_FILE)
		return (ERROR);
	return (EXECUTED);
}

int	syntax_errors(t_data *data)
{
	if (last_pipe(data) == ERROR)
	{
		printf("This wand ain't required by subject |last pipe|");
		return (ERROR);
	}
	return (EXECUTED);
}
