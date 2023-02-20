/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:56:37 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 16:48:23 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cnt;
	char	*ptr;
	char	*ptr1;

	ptr = (char *)dst;
	ptr1 = (char *)src;
	if (ptr1 == 0 && ptr == 0)
		return (NULL);
	cnt = 0;
	while (cnt < n)
	{
		*(ptr + cnt) = *(ptr1 + cnt);
		cnt++;
	}	
	return (ptr);
}
