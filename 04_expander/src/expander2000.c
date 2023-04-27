/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2000.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:40:47 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/27 13:45:15 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

static char	*expand_quest(char *temp, t_data *data)
{
	char	*itoa;

	itoa = ft_itoa(data->exit_status);
	if (itoa == NULL)
		return (NULL);
	temp = ft_strjoin2(temp, itoa, 0, 0);
	return (free(itoa), temp);
}

static char	*i_am_back(char *temp, t_data *data, char **tokens, int cnt1)
{
	char	*needle;

	needle = search_needle(data, tokens[cnt1]);
	if (needle != NULL)
		temp = ft_strjoin2(temp, needle
				+ ft_strlen(tokens[cnt1]) + 1, 0, 0);
	return (temp);
}

char	*expand_tokens_helper(t_data *data, char *temp, int q, char **tokens)
{
	int		cnt1;
	int		action;

	cnt1 = 0;
	while (tokens[cnt1] != NULL)
	{
		q = q_state(tokens[cnt1], 0, q);
		action = action_calculation(data, q, tokens, cnt1);
		if (action == EXECUTED)
			temp = ft_strjoin2(temp, tokens[cnt1], 0, 0);
		else if (action == ADD)
		{
			cnt1++;
			temp = i_am_back(temp, data, tokens, cnt1);
		}
		else if (action == 2)
		{
			cnt1++;
			temp = expand_quest(temp, data);
		}
		cnt1++;
	}
	return (temp);
}
