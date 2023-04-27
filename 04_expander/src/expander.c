/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:38:42 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/27 13:42:34 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

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

int	action_calculation(int q, char **tokens, int cnt1)
{
	//char	*needle;

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
	//needle = search_needle(data, tokens[cnt1 + 1]);
	// @note set but not used?
	if ((is_white_space(*(tokens[cnt1 + 1])) == 1
			|| *(tokens[cnt1 + 1]) == 34 || *(tokens[cnt1 + 1]) == 39)
		&& q == 34)
		return (EXECUTED);
	if ((*(tokens[cnt1 + 1]) == 34 || *(tokens[cnt1 + 1]) == 39) && q == 0)
		return (3);
	return (ADD);
}

int	expand_line(t_data *data, int cnt, int q)
{
	char	**tokens;
	char	*temp;

	temp = NULL;
	if (data->combine[cnt].combined_str == NULL)
	{
		data->combine[cnt].combined_str = ft_strdup("");
		if (data->combine[cnt].combined_str == NULL)
			return (ERROR);
	}
	tokens = tokenizer(data->combine[cnt].combined_str, 0, 0, 0);
	if (tokens == NULL)
		return (ERROR);
	temp = expand_tokens_helper(data, temp, q, tokens);
	free(data->combine[cnt].combined_str);
	data->combine[cnt].combined_str = temp;
	split_free(tokens);
	return (EXECUTED);
}
