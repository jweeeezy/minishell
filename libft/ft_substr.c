/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:46:06 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/03 01:23:10 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	cnt;

	cnt = 0;
	if ((size_t)ft_strlen((char *)s) < len)
		sub = ft_calloc((size_t)ft_strlen((char *)s) + 1, sizeof(char));
	else
		sub = ft_calloc(len + 1, sizeof(char));
	if (sub == NULL || s == NULL)
		return (NULL);
	if ((size_t)ft_strlen((char *)s) < start)
		return (sub);
	while (cnt < len && *(s + cnt + start) != '\0')
	{
		*(sub + cnt) = *(s + cnt + start);
		cnt++;
	}
	return (sub);
}
