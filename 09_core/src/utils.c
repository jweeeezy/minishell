/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:30:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/17 19:25:28 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

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

char	*ft_charjoin(char *temp, char c, size_t cnt1, size_t cnt2)
{
	char	*new_temp;

	new_temp = NULL;
	if (temp == NULL)
	{
		temp = malloc(sizeof(char));
		*temp = '\0';
	}
	if (temp == NULL)
		return (NULL);
	new_temp = malloc((ft_strlen(temp) + 2) * sizeof(char));
	if (new_temp == NULL)
		return (NULL);
	while (*(temp + cnt1) != '\0')
	{
		*(new_temp + cnt1) = *(temp + cnt1);
		cnt1++;
	}
	*(new_temp + cnt1 + cnt2) = c;
	cnt2++;
	*(new_temp + cnt1 + cnt2) = '\0';
	return (free(temp), new_temp);
}

int	only_whites(char *str)
{
	int	cnt;

	cnt = 0;
	if (str == NULL)
		return (ADD);
	while (str[cnt] != '\0')
	{
		if (is_white_space(str[cnt]) == 0)
			return (EXECUTED);
		cnt++;
	}
	return (ADD);
}

int	is_command_mixed(char *str, char *token)
{
	char	*temp;
	int		cnt;

	cnt = 0;
	temp = NULL;
	while (str[cnt] != '\0')
	{
		temp = ft_charjoin(temp, ft_tolower(str[cnt]), 0, 0);
		if (temp == NULL)
			return (ERROR);
		cnt++;
	}
	if (ft_strlen(temp) == ft_strlen(token)
		&& ft_strnstr(temp, token, ft_strlen(temp)) != NULL)
		return (free(temp), ADD);
	return (free(temp), EXECUTED);
}

int	is_command(char *str, char *token)
{
	if (ft_strlen(str) == ft_strlen(token)
		&& ft_strnstr(str, token, ft_strlen(str)) != NULL)
		return (ADD);
	return (EXECUTED);
}
