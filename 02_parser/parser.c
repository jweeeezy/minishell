/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/01 15:06:55 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (data->execute[0].order_numb < 1 && data->execute[0] != NULL)
	{
		data->execute[0].order_numb;

	}
	if (cnt == 21)
		echo(data, 0);
	return (EXECUTED);
}
