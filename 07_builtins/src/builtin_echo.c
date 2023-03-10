/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/10 15:34:53 by kvebers          ###   ########.fr       */
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
	int	temp;

	temp = cnt - 1;
	if (data->string != NULL)
		free(data->string);
	data->string = NULL;
	while (data->execute[cnt].order_numb == WHITE && cnt < data->tokens)
		cnt++;
	if (data->tokens > cnt
		&& ft_strncmp(data->execute[cnt].order_str, "-n", 2) == 0
		&& ft_strlen(data->execute[cnt].order_str) == 2
		&& ft_strncmp(data->execute[temp].order_str, "echo", 4) == 0)
		return (cnt);
	return (EXECUTED);
}


static int	check_quote_state(t_data *data, int cnt)
{
	int	quote_check;
	int	quote_id;
	int	cnt1;

	cnt1 = 0;
	quote_check = 0;
	quote_id = 0;
	while (cnt1 < cnt && cnt1 < data->tokens)
	{
		if ((data->execute[cnt1].order_numb == 3
				|| data->execute[cnt1].order_numb == 4) && quote_check == 0)
		{
			quote_check = 1;
			quote_id = data->execute[cnt1].order_numb;
		}
		else if (quote_id == data->execute[cnt1].order_numb)
		{
			quote_check = 0;
			quote_id = 0;
		}
		cnt1++;
	}
	return (quote_id);
}

int	echo_join(t_data *data, int cnt)
{
	int	quote_state;

	quote_state = check_quote_state(data, cnt);
	if (data->execute[cnt].order_numb == APOSTROPHE
		|| data->execute[cnt].order_numb == QUOTATION_MARK
		|| data->execute[cnt].order_numb == DOLLA)
		return (EXECUTED);
	else if (quote_state == 0)
		data->string = ft_strjoin2(data->string,
				data->execute[cnt].order_str, 0, 0);
	else if (quote_state == 3
		&& data->execute[cnt].order_numb == STRING
		&& data->execute[cnt - 1].order_numb == DOLLA)
		data->string = ft_strjoin2(data->string, "test", 0, 0);
	else if (quote_state != 0)
		data->string = ft_strjoin2(data->string,
				data->execute[cnt].order_str, 0, 0);
	if (data->string == NULL)
		return (ERROR);
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
		if (echo_join(data, cnt) == ERROR)
			return (ERROR);
		cnt++;
	}
	return (cnt);
}
