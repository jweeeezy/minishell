/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:39:41 by kvebers           #+#    #+#             */
/*   Updated: 2022/12/06 12:34:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr2(const char *s, int c)
{
	char	*ptr;

	if (s == NULL)
		return (NULL);
	ptr = (char *)s;
	c = c % 256;
	while (*ptr != c && *ptr != '\0')
		ptr++;
	if (*ptr == c)
		return (ptr);
	return (NULL);
}

char	*ft_strjoin2(char *temp, char *buffer, size_t cnt1, size_t cnt2)
{
	char	*new_temp;

	if (temp == NULL)
	{
		temp = malloc(sizeof(char));
		*temp = '\0';
	}
	if (temp == NULL || buffer == NULL)
		return (NULL);
	new_temp = malloc((ft_strlen(buffer) + ft_strlen(temp) + 1) * sizeof(char));
	if (new_temp == NULL)
		return (NULL);
	while (*(temp + cnt1) != '\0')
	{
		*(new_temp + cnt1) = *(temp + cnt1);
		cnt1++;
	}
	while (*(buffer + cnt2) != '\0')
	{
		*(new_temp + cnt1 + cnt2) = *(buffer + cnt2);
		cnt2++;
	}
	*(new_temp + cnt1 + cnt2) = '\0';
	return (free(temp), new_temp);
}
