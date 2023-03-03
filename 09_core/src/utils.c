/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:30:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/01 11:06:31 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libme.h"

int	is_command1(t_data *data, int cnt, char *needle)
{
	int		cnt1;

	cnt1 = ft_strnstr2(data->args[cnt], needle, ft_strlen(data->args[cnt]));
	if (cnt1 >= 0)
	{
		if (utils_is_command_helper(data, cnt1, cnt) > 1)
			return (EXECUTED);
		else if (utils_is_command_helper(data, cnt1, cnt) < 1
			&& utils_is_command_helper1(data, cnt1, cnt, needle) == ADD)
			return (ADD);
	}
	return (EXECUTED);
}

int	is_command(t_data *data, int cnt, char *needle)
{
	char	*upper_to_lower;
	int		cnt1;

	cnt1 = 0;
	upper_to_lower = ft_strdup(data->args[cnt]);
	if (upper_to_lower == NULL)
		return (ERROR);
	while (upper_to_lower[cnt1] != '\0')
	{
		upper_to_lower[cnt1] = ft_tolower(upper_to_lower[cnt1]);
		cnt1++;
	}
	cnt1 = ft_strnstr2(upper_to_lower, needle, ft_strlen(data->args[cnt]));
	if (cnt1 >= 0)
	{
		if (utils_is_command_helper(data, cnt1, cnt) > 1)
			return (free(upper_to_lower), EXECUTED);
		else if (utils_is_command_helper(data, cnt1, cnt) < 1
			&& utils_is_command_helper1(data, cnt1, cnt, needle) == 1)
			return (free(upper_to_lower), ADD);
	}
	return (free(upper_to_lower), EXECUTED);
}

int	utils_is_command_helper1(t_data *data, int cnt2, int cnt, char *needle)
{
	cnt2 = cnt2 + ft_strlen(needle);
	if (is_white_space(*(data->args[cnt] + cnt2))
		|| *(data->args[cnt] + cnt2) == '\0')
		return (ADD);
	return (EXECUTED);
}

int	utils_is_command_helper(t_data *data, int cnt1, int cnt)
{
	int	cnt2;
	int	sum;

	cnt2 = 0;
	sum = 0;
	while (cnt2 < cnt1)
	{
		if (is_white_space(*(data->args[cnt] + cnt2)))
		{
		}
		else
			sum++;
		cnt2++;
	}
	return (sum);
}

int	ft_strnstr2(const char *haystack, const char *needle, size_t t)
{
	size_t	cnt1;
	size_t	cnt2;
	char	*h_ptr;
	char	*n_ptr;

	h_ptr = (char *)haystack;
	n_ptr = (char *)needle;
	cnt1 = 0;
	if (*n_ptr == '\0')
		return (ERROR);
	while (t != 0 && *(h_ptr + cnt1) != '\0')
	{
		cnt2 = 0;
		while (cnt1 + cnt2 < t && *(h_ptr + cnt1 + cnt2) == *(n_ptr + cnt2))
		{
			if (*(h_ptr + cnt2 + cnt1) == '\0' && *(n_ptr + cnt2) == '\0')
				return (cnt1);
			cnt2++;
		}
		if (*(n_ptr + cnt2) == '\0')
			return (cnt1);
		cnt1++;
	}
	return (ERROR);
}
