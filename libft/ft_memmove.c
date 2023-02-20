/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:25:07 by kvebers           #+#    #+#             */
/*   Updated: 2022/10/30 15:54:04 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	cnt;
	char	*ptr;
	char	*ptr1;

	ptr = (char *)dst;
	ptr1 = (char *)src;
	cnt = 0;
	if (ptr1 == 0 && ptr == 0)
		return (NULL);
	if (ptr > ptr1)
	{
		while (len > 0)
		{
			len--;
			*(ptr + len) = *(ptr1 + len);
		}
		return (dst);
	}
	while (cnt < len)
	{
		*(ptr + cnt) = *(ptr1 + cnt);
		cnt++;
	}
	return (dst);
}
