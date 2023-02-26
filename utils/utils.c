/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:30:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 15:49:11 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	utils_is_command_helper1(t_data *data, int cnt2, int cnt, char *needle)
{
	cnt2 = cnt2 + ft_strlen(needle);
	if (*(data->args[cnt] + cnt2) == ' '
		|| *(data->args[cnt] + cnt2) == '\t'
		|| *(data->args[cnt] + cnt2) == '\t'
		|| *(data->args[cnt] + cnt2) == '\n'
		|| *(data->args[cnt] + cnt2) == '\r'
		|| *(data->args[cnt] + cnt2) == '\v'
		|| *(data->args[cnt] + cnt2) == '\f'
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
		if (*(data->args[cnt] + cnt2) == ' '
			|| *(data->args[cnt] + cnt2) == '\t'
			|| *(data->args[cnt] + cnt2) == '\t'
			|| *(data->args[cnt] + cnt2) == '\n'
			|| *(data->args[cnt] + cnt2) == '\r'
			|| *(data->args[cnt] + cnt2) == '\v'
			|| *(data->args[cnt] + cnt2) == '\f')
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
