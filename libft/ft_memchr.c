/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:23:53 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 23:03:34 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	int		cnt;

	cnt = 0;
	ptr = (char *)s;
	c = c % 256;
	while (n != 0)
	{
		if (*(ptr + cnt) == c)
			return (ptr + cnt);
		cnt++;
		n--;
	}
	return (NULL);
}
