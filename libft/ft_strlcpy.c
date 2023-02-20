/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:59:11 by kvebers           #+#    #+#             */
/*   Updated: 2022/10/23 10:07:04 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	size;

	size = 0;
	while (dstsize == 0 && *(src + size) != '\0')
		size++;
	while ((*(src + size) != '\0') && (size < dstsize - 1))
	{
		*(dst + size) = *(src + size);
		size++;
	}
	if (size < dstsize)
		*(dst + size) = '\0';
	while (*(src + size) != '\0')
		size++;
	return (size);
}
