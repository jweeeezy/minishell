/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:22:56 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 17:56:45 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	counter1;
	size_t	counter2;
	size_t	counter3;
	char	*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	counter1 = ft_strlen((char *)s1);
	counter2 = ft_strlen((char *)s2);
	counter3 = 0;
	dest = ft_calloc((counter1 + counter2 + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (counter3 < counter1)
	{
		*(dest + counter3) = *(s1 + counter3);
		counter3++;
	}
	counter3 = 0;
	while (counter3 < counter2)
	{
		*(dest + counter1 + counter3) = *(s2 + counter3);
		counter3++;
	}
	return (dest);
}
