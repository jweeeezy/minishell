/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:02:58 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/13 17:17:36 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	check_space_stat(t_data *data, int cnt)
{
	if (data->execute[cnt].order_numb == APOSTROPHE
		|| data->execute[cnt].order_numb == QUOTATION_MARK)
		return (EXECUTED);
	if (cnt -1 >= 0 && data->execute[cnt].order_numb == WHITE
		&& data->execute[cnt].order_numb == WHITE)
		return (EXECUTED);
	return (ADD);
}

int	no_quote(t_data *data, int cnt, int cnt1)
{
	if (check_space_stat(data, cnt) == ADD)
	{
		if (strjoin_with_extra_steps(data, cnt, cnt1) == ERROR)
			return (ERROR);
	}
	return (EXECUTED);
}
