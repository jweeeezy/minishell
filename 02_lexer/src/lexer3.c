/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:31:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 13:57:50 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

char	*open_quotes(char *str)
{
	int		q;
	int		cnt;
	char	*temp;

	q = 0;
	cnt = 0;
	temp = NULL;
	while (str[cnt] != '\0')
	{
		q = q_state(str, cnt, q);
		if (q == str[cnt])
		{
		}
		else if (q == 0 && (str[cnt] == 34 || str[cnt] == 39))
		{	
		}
		else
		{
			temp = ft_charjoin(temp, str[cnt], 0, 0);
			if (temp == NULL)
				return (NULL);
		}
		cnt++;
	}
	return (temp);
}

int	remove_quotes(t_data *data, int cnt, int cnt1)
{
	char	*temp;

	while (cnt1 < data->combine[cnt].count_n)
	{
		temp = NULL;
		temp = open_quotes(data->combine[cnt].execute[cnt1].order_str);
		if (temp == NULL)
		{
			if (data->combine[cnt].execute[cnt1].order_numb != WHITE)
				data->combine[cnt].execute[cnt1].order_numb = QUOTATION_MARK;
				temp = ft_strdup("");
			if (temp == NULL)
				return (ERROR);
		}
		free(data->combine[cnt].execute[cnt1].order_str);
		data->combine[cnt].execute[cnt1].order_str = NULL;
		data->combine[cnt].execute[cnt1].order_str = ft_strdup(temp);
		free(temp);
		if (data->combine[cnt].execute[cnt1].order_str == NULL)
			return (ERROR);
		cnt1++;
	}
	return (EXECUTED);
}

int	remove_null(t_data *data, int cnt)
{
	if (data->combine[cnt].combined_str == NULL)
	{
		data->combine[cnt].combined_str = ft_strdup("");
		if (data->combine[cnt].combined_str == NULL)
			return (ERROR);
	}
	return (EXECUTED);
}

int	remove_whitespaces(t_data *data, int cnt)
{
	int		cnt1;

	cnt1 = 0;
	while (cnt1 < data->combine[cnt].count_n)
	{
		if (only_whites(data->combine[cnt].execute[cnt1].order_str) == ADD)
		{
			free(data->combine[cnt].execute[cnt1].order_str);
			data->combine[cnt].execute[cnt1].order_numb = WHITE;
			data->combine[cnt].execute[cnt1].order_str = ft_strdup("");
			if (data->combine[cnt].execute[cnt1].order_str == NULL)
				return (ERROR);
		}
		cnt1++;
	}
	return (EXECUTED);
}
