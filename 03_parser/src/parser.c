/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/01 17:59:27 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_data *data)
{
	int	cnt;
	int	wait_for_pipes;

	cnt = 0;
	wait_for_pipes = 0;
	while (cnt < data->tokens)
	{
		if (data->execute[cnt].order_numb > 1)
		{
			wait_for_pipes = 1;
//			execute_command(data, cnt);
		}
		cnt++;
	}
	return (EXECUTED);
}
