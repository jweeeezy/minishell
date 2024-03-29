/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:49:30 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/26 12:58:46 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

int	remove_edge_case_helper(t_data *data, int cnt, int cnt1)
{
	if (data->combine[cnt].combined_str == NULL
		|| ft_strlen(data->combine[cnt].combined_str) == 0)
		return (ERROR);
	if (data->combine[cnt].combined_str[cnt1] == '<'
		|| data->combine[cnt].combined_str[cnt1] == '>')
		return (EXECUTED);
	return (ERROR);
}

int	remove_edge_case1(t_data *data, int cnt, int cnt1)
{
	char	*temp;

	temp = NULL;
	if (remove_edge_case_helper(data, cnt, cnt1) == ERROR)
		return (EXECUTED);
	while (data->combine[cnt].combined_str[cnt1] != '\0'
		&& (data->combine[cnt].combined_str[cnt1] == '<'
			|| data->combine[cnt].combined_str[cnt1] == '>'))
	{
		temp = ft_charjoin(temp, data->combine[cnt].combined_str[cnt1], 0, 0);
		cnt1++;
	}
	while (data->combine[cnt].combined_str[cnt1] != '\0'
		&& is_white_space(data->combine[cnt].combined_str[cnt1]) == ADD)
		cnt1++;
	while (data->combine[cnt].combined_str[cnt1] != '\0')
	{
		temp = ft_charjoin(temp, data->combine[cnt].combined_str[cnt1], 0, 0);
		cnt1++;
	}
	free(data->combine[cnt].combined_str);
	data->combine[cnt].combined_str = temp;
	return (EXECUTED);
}
