/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/12 14:47:44 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"    

int	count_split(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	split_free(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
	{
		free(split[cnt]);
		cnt++;
	}
	free(split);
}

int	q_state(char *str, int cnt, int quote_state)
{
	if (str[cnt] == 34 && quote_state == 0)
		quote_state = 34;
	else if (str[cnt] == 39 && quote_state == 0)
		quote_state = 39;
	else if (str[cnt] == 39 && quote_state == 39)
		quote_state = 0;
	else if (str[cnt] == 34 && quote_state == 34)
		quote_state = 0;
	return (quote_state);
}

char	*ft_strnstr3(const char *haystack, const char *needle, size_t length)
{
	size_t	index;
	size_t	counter_needle;
	size_t	needle_len;

	index = 0;
	counter_needle = 0;
	needle_len = ft_strlen(needle);
	if (needle_len <= 0)
		return ((char *) haystack);
	while (index < length && haystack[index] != '\0'
		&& index < needle_len)
	{
		if (haystack[index] == needle[counter_needle])
			counter_needle++;
		else
			counter_needle = 0;
		index++;
	}
	if (counter_needle == needle_len)
		return ((char *) haystack + index - counter_needle);
	else
		return (NULL);
}
