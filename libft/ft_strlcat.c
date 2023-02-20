/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:46:23 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 17:05:56 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;
	size_t	cnt1;
	size_t	dst_len;

	cnt = 0;
	cnt1 = 0;
	if (dst == 0 && dstsize == 0)
		return (0);
	dst_len = ft_strlen(dst);
	cnt = dst_len;
	if (dstsize < cnt)
		return (ft_strlen((char *)src) + dstsize);
	while ((cnt + 1) < dstsize && *(src + cnt1) != '\0')
	{
		*(dst + cnt) = *(src + cnt1);
		cnt++;
		cnt1++;
	}
	*(dst + cnt) = '\0';
	return (ft_strlen((char *)src) + dst_len);
}
