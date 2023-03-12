/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:30:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/12 20:23:49 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

char	*search_needle(t_data *data, char *needle)
{
	char		*result_str;
	t_expander	*current_node;

	current_node = data->expander;
	result_str = NULL;
	while (current_node != NULL && result_str == NULL)
	{
		if (ft_strnstr(current_node->str, needle,
				ft_strlen(current_node->str)) != NULL)
			return (current_node->str);
		current_node = current_node->next;
	}
	return (NULL);
}

int	dolla_handler(t_data *data, int cnt, int cnt1)
{
	char	*dolla;

	if (cnt + 1 < data->tokens && data->execute[cnt + 1].order_numb != WHITE
		&& is_pipe(data->execute[cnt + 1].order_numb) != ADD)
	{
		dolla = search_needle(data, data->execute[cnt + 1].order_str);
		if (dolla != NULL)
		{
			data->combine[cnt1].combined_str
				= ft_strjoin2(data->combine[cnt1].combined_str, dolla, 0, 0);
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
