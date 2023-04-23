/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:38:42 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/23 12:30:10 by kvebers          ###   ########.fr       */
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

int	action_calculation(t_data *data, int q, char **tokens, int cnt1)
{
	char	*needle;

	if (*(tokens[cnt1]) != '$')
		return (EXECUTED);
	if (q == 39)
		return (EXECUTED);
	if (tokens[cnt1 + 1] == NULL)
		return (EXECUTED);
	if (*(tokens[cnt1 + 1]) == '?')
		return (2);
	if (*(tokens[cnt1 + 1]) == '/')
		return (EXECUTED);
	needle = search_needle(data, tokens[cnt1 + 1]);
	if ((is_white_space(*(tokens[cnt1 + 1])) == 1
			|| *(tokens[cnt1 + 1]) == 34 || *(tokens[cnt1 + 1]) == 39)
			&& q == 34)
		return (EXECUTED);
	if ((*(tokens[cnt1 + 1]) == 34 || *(tokens[cnt1 + 1]) == 39) && q == 0)
		return (3);
	return (ADD);
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

int	expand_line(t_data *data, int cnt, int q)
{
	char	**tokens;
	char	*temp;

	temp = NULL;
	tokens = tokenizer(data->combine[cnt].combined_str, 0, 0, 0);
	if (tokens == NULL)
		return (ERROR);
	temp = expand_tokens_helper(data, temp, q, tokens);
	free(data->combine[cnt].combined_str);
	data->combine[cnt].combined_str = temp;
	split_free(tokens);
	return (EXECUTED);
}
