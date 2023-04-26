/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:58:09 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/26 17:55:23 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include "pies.h"

int	check_pies2(char *str)
{
	if (ft_strnstr(str, PIE_1, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_2, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_3, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_4, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_5, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_6, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_8, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_9, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_10, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_11, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_12, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_13, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_14, ft_strlen(str)) != NULL
		|| ft_strnstr(str, PIE_15, ft_strlen(str)) != NULL)
		return (ERROR);
	return (EXECUTED);
}

// int	check_pies1(char *str)
// {
// 	int	cnt;

// 	cnt = 0;
// 	while (str[cnt])
// 	{
// 		if (str[cnt + 1] == '\0')
// 			return (EXECUTED);
// 		if (str[cnt] == '<' || str[cnt] == '>' || str[cnt] == '|')
// 		{
// 			if (str[cnt + 1] == '<' || str[cnt + 1] == '>'
// 				|| str[cnt + 1] == '|')
// 			{
// 				if (str[cnt] != str[cnt + 1])
// 					return (ERROR);
// 			}
// 		}
// 		cnt++;
// 	}
// 	return (EXECUTED);
// }

int	check_pies(t_data *data, int q)
{
	char	*str;
	int		cnt;

	cnt = 0;
	str = NULL;
	while (data->line[cnt] != '\0')
	{
		q = q_state(data->line, cnt, q);
		if (is_white_space(data->line[cnt]) == 0 && q == 0)
			str = ft_charjoin(str, data->line[cnt], 0, 0);
		cnt++;
	}
	if (str != NULL)
	{
		if (check_pies2(str))
		{
			ft_putstr_fd("ERROR Wierd Pies and stuff\n", 2);
			data->exit_status = 2;
			return (free(str), ERROR);
		}
		free(str);
	}
	return (EXECUTED);
}
