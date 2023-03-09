/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/09 17:56:20 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>


static int	count_till_pipe(t_data *data, int cnt)
{
	int	quote_check;
	int	quote_id;

	quote_check = 0;
	while (cnt < data->tokens)
	{
		if (quote_check == 0
			&& is_pipe(data->execute[cnt].order_numb) == ADD)
			return (cnt);
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
	return (cnt);
}

static int	check_string_state(t_data *data, int cnt)
{
	if (data->string != NULL)
		free(data->string);
	data->string = NULL;
	if (data->tokens >= cnt + 1
		&& ft_strncmp(data->execute[cnt + 1].order_str, "-ne", 3) == 0
		&& ft_strlen(data->execute[cnt + 1].order_str) == 3
		&& ft_strncmp(data->execute[cnt - 1].order_str, "echo", 4) == 0)
		return (WHITE);
	return (EXECUTED);
}

int	echo(t_data *data, int cnt)
{
	int	new_line;
	int	counter;

	new_line = check_string_state(data, cnt);
	counter = count_till_pipe(data, cnt);
	cnt = cnt + new_line;
	while (cnt < counter && cnt < data->tokens)
	{
		printf("%s", data->execute[cnt].order_str);
		cnt++;
	}
	if (new_line == 0)
		printf("\n");
	return (cnt);
}
