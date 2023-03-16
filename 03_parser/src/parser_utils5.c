/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:23:13 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/14 19:08:09 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

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

int	recheck_the_main_command(t_data *data, int cnt)
{
	int		cnt1;

	cnt1 = 0;
	while (*(data->combine[cnt].combined_str + cnt1) != '\0'
		&& is_white_space(*(data->combine[cnt].combined_str + cnt1)) == EXECUTED
		&& is_pipe(*(data->combine[cnt].combined_str + cnt1)) == EXECUTED)
			cnt1++;
	free(data->combine[cnt].command->order_str);
	data->combine[cnt].command->order_str = malloc(sizeof(char) * (cnt1 + 1));
	if (ft_strlcpy(data->combine[cnt].command->order_str,
			data->combine[cnt].combined_str, cnt1) == 0)
		return (ERROR);
	printf("%s\n", data->combine[cnt].command->order_str);
	return (EXECUTED);
}
