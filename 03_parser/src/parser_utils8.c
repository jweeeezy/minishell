/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:01:44 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/30 12:02:20 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

static int	retoken_helper_helper(t_data *data, int cnt, char **split)
{
	char	*temp;
	size_t	cnt1;

	cnt1 = 0;
	temp = ft_strdup(data->combine[cnt + 1].combined_str + ft_strlen(split[0]));
	if (temp == NULL)
		return (ERROR);
	while (cnt1 < ft_strlen(temp) && is_white_space(temp[cnt1]) == ADD)
		cnt1++;
	free(temp);
	temp = ft_strdup(data->combine[cnt + 1].combined_str
			+ ft_strlen(split[0]) + cnt1);
	free(data->combine[cnt + 1].combined_str);
	data->combine[cnt + 1].combined_str = NULL;
	if (temp != NULL)
		data->combine[cnt + 1].combined_str = temp;
	return (EXECUTED);
}

static int	retoken_helper(t_data *data, int cnt, char **split, int numb)
{
	int	cn;

	cn = 1;
	if (numb == 0)
		return (ERROR);
	data->combine[cnt].combined_str
		= ft_strjoin2(data->combine[cnt].combined_str, " ", 0, 0);
	if (data->combine[cnt].combined_str == NULL)
		return (ERROR);
	data->combine[cnt].combined_str
		= ft_strjoin2(data->combine[cnt].combined_str, split[0], 0, 0);
	if (data->combine[cnt].combined_str == NULL)
		return (ERROR);
	if (retoken_helper_helper(data, cnt, split) == ERROR)
		return (ERROR);
	return (EXECUTED);
}

int	retokenize_the_commands(t_data *data, int cnt)
{
	char	**split;
	int		split_tokens;

	split = NULL;
	if (cnt + 1 >= data->commands_to_process)
		return (ERROR);
	split = ft_split(data->combine[cnt + 1].combined_str, ' ');
	if (split == NULL)
		return (ERROR);
	split_tokens = count_split(split);
	if (retoken_helper(data, cnt, split, split_tokens) == ERROR)
	{
		split_free(split);
		return (ERROR);
	}
	split_free(split);
	return (EXECUTED);
}
