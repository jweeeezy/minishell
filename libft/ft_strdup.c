/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:13:55 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 16:31:01 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		counter;
	int		counter1;
	char	*dest;

	counter = 0;
	counter1 = 0;
	while (*(s1 + counter) != '\0')
		counter++;
	dest = ft_calloc((counter + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (counter1 < counter)
	{
		*(dest + counter1) = *(s1 + counter1);
		counter1++;
	}
	return (dest);
}
