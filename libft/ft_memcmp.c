/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:44:33 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 17:14:28 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	c;
	char	*ptr;
	char	*ptr1;

	ptr = (char *)str1;
	ptr1 = (char *)str2;
	c = 0;
	if (n == 0)
		return (0);
	while (c < (n - 1))
	{
		if (*(ptr + c) != *(ptr1 + c))
			return ((unsigned char) *(ptr + c) - (unsigned char )*(ptr1 + c));
		c++;
	}
	return ((unsigned char) *(ptr + c) - (unsigned char )*(ptr1 + c));
}
