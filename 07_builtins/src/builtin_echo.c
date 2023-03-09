/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/09 15:48:00 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>


static int	check_string_state(t_data *data, int cnt)
{
	if (data->string != NULL)
		free(data->string);
	data->string = NULL;
	if (data->tokens >= cnt + 2
		&& ft_strncmp(data->execute[cnt + 2].order_str, "-ne", 3) == 0
		&& ft_strlen(data->execute[cnt + 2].order_str) == 3)
		return (ADD);
	return (EXECUTED);
}

int	echo(t_data *data, int cnt)
{
	int	new_line;
	int	quote_open;
	//int save_quote;

	quote_open = 1;
	new_line = check_string_state(data, cnt);
	// while (is_pipe(data->execute[cnt].order_numb) + quote_open <= ADD
	// 	&& cnt < data->tokens)
	// {
	// 	if (data->execute[cnt].order_numb == 3 || )
	// 	cnt++;
	// }
	return (cnt);
}
