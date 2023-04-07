/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:30:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/27 15:11:43 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

char	*search_needle(t_data *data, char *needle)
{
	char		*temp_needle;
	int			cnt;

	temp_needle = ft_strjoin(needle, "=");
	if (temp_needle == NULL)
		return (NULL);
	cnt = 0;
	if (data->envp == NULL)
		return (NULL);
	while (data->envp[cnt] != NULL)
	{
		if (ft_strnstr3(data->envp[cnt], temp_needle,
				ft_strlen(data->envp[cnt])) != NULL)
			return (free(temp_needle), data->envp[cnt]);
		cnt++;
	}
	return (free(temp_needle), NULL);
}

int	dolla_handler(t_data *data, int cnt, int cnt1)
{
	char	*dolla;
	char	*dolla_offset;

	if (cnt + 1 < data->tokens && data->execute[cnt + 1].order_numb != WHITE
		&& is_pipe(data->execute[cnt + 1].order_numb) != ADD)
	{
		dolla = search_needle(data, data->execute[cnt + 1].order_str);
		if (dolla != NULL)
		{
			dolla_offset = dolla
				+ ft_strlen(data->execute[cnt + 1].order_str) + 1;
			data->combine[cnt1].combined_str
				= ft_strjoin2(data->combine[cnt1].combined_str,
					dolla_offset, 0, 0);
			return (EXECUTED);
		}
		return (EXECUTED);
	}
	return (ERROR);
}

int	handle_quotes(t_data *data, int cnt, int cnt1)
{
	if (data->execute[cnt].order_numb == DOLLA)
	{
		if (dolla_handler(data, cnt, cnt1) == ERROR)
			return (ERROR);
		return (ADD);
	}
	else
		strjoin_with_extra_steps(data, cnt, cnt1);
	return (EXECUTED);
}

int	parser_return_q_m(t_data *data, int cnt, int cnt1)
{
	int	state;

	state = handle_quotes(data, cnt, cnt1);
	if (state == ERROR)
		return (ERROR);
	else if (state == ADD)
		return (ADD);
	else
		return (EXECUTED);
}

int	parser_return_a(t_data *data, int cnt, int cnt1)
{
	int	state;

	state = no_quote(data, cnt, cnt1);
	if (state == ERROR)
		return (ERROR);
	else if (state == ADD)
		return (ADD);
	else
		return (EXECUTED);
}
