/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:07:12 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 16:53:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			c;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	c = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while ((*(ptr1 + c) == *(ptr2 + c)) && (c < n) && (*(ptr2 + c) != '\0'))
		c++;
	if (c != n)
		return ((*(ptr1 + c) - *(ptr2 + c)));
	return (0);
}
