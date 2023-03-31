/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:23:13 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/30 14:37:33 by kvebers          ###   ########.fr       */
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

int	is_command2(char *str, char *str1)
{
	char	*upper_to_lower;
	int		cnt;

	cnt = 0;
	upper_to_lower = ft_strdup(str);
	if (upper_to_lower == NULL)
		return (ERROR);
	while (upper_to_lower[cnt] != '\0')
	{
		upper_to_lower[cnt] = ft_tolower(upper_to_lower[cnt]);
		cnt++;
	}
	if (ft_strnstr(upper_to_lower, str1, ft_strlen(str1)) != NULL
		&& ft_strlen(str) == ft_strlen(str1))
		return (ADD);
	return (EXECUTED);
}

int	calculate_command(char *str)
{
	if (ft_strlen("cd") == ft_strlen(str) && ft_strnstr(str, "cd", 2))
		return (CD);
	else if (ft_strlen("export") == ft_strlen(str)
		&& ft_strnstr(str, "export", 6))
		return (EXPORT);
	else if (ft_strlen("unset") == ft_strlen(str)
		&& ft_strnstr(str, "unset", 5))
		return (UNSET);
	else if (ft_strlen("exit") == ft_strlen(str) && ft_strnstr(str, "exit", 4))
		return (EXIT);
	else if (ft_strlen("env") == ft_strlen(str) && ft_strnstr(str, "env", 3))
		return (ENV);
	else if (is_command2(str, "echo") == ADD)
		return (ECHO);
	else if (is_command2(str, "pwd") == ADD)
		return (PWD);
	return (STRING);
}

int	recheck_the_main_command(t_data *data, int cnt)
{
	int		cnt1;

	cnt1 = 0;
	while (*(data->combine[cnt].combined_str + cnt1) != '\0'
		&& is_white_space(*(data->combine[cnt].combined_str + cnt1)) == EXECUTED
		&& is_pipe(*(data->combine[cnt].combined_str + cnt1)) == EXECUTED)
			cnt1++;
	if (data->combine[cnt].command->order_str != NULL)
		free(data->combine[cnt].command->order_str);
	data->combine[cnt].command->order_str = malloc(sizeof(char) * (cnt1 + 1));
	if (ft_strlcpy(data->combine[cnt].command->order_str,
			data->combine[cnt].combined_str, cnt1 + 1) == 0)
		return (ERROR);
	data->combine[cnt].command->order_numb
		= calculate_command(data->combine[cnt].command->order_str);
	return (EXECUTED);
}
