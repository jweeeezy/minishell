/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:35:08 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 21:25:19 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t t)
{
	size_t	cnt1;
	size_t	cnt2;
	char	*h_ptr;
	char	*n_ptr;

	h_ptr = (char *)haystack;
	n_ptr = (char *)needle;
	cnt1 = 0;
	if (*n_ptr == '\0')
		return (h_ptr);
	while (t != 0 && *(h_ptr + cnt1) != '\0')
	{
		cnt2 = 0;
		while (cnt1 + cnt2 < t && *(h_ptr + cnt1 + cnt2) == *(n_ptr + cnt2))
		{
			if (*(h_ptr + cnt2 + cnt1) == '\0' && *(n_ptr + cnt2) == '\0')
				return (h_ptr + cnt1);
			cnt2++;
		}
		if (*(n_ptr + cnt2) == '\0')
			return (h_ptr + cnt1);
		cnt1++;
	}
	return (NULL);
}
