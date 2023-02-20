/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:07:01 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 18:15:44 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	cnt;
	char	*dest;

	cnt = 0;
	if (s == NULL)
		return (NULL);
	dest = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (dest == NULL || f == NULL)
		return (NULL);
	while (*(s + cnt) != '\0')
	{
		*(dest + cnt) = (f)(cnt, *(s + cnt));
		cnt++;
	}
	return (dest);
}
