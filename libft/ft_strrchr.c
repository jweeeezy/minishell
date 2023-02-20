/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:07:07 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 23:35:04 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		temp;
	char	*ptr;
	int		cnt;
	int		isfound;

	ptr = (char *)s;
	temp = 0;
	cnt = 0;
	isfound = 0;
	if (*ptr == '\0' && (c % 256) == '\0')
		return (ptr);
	while (*(ptr + cnt) != '\0')
	{
		if (*(ptr + cnt) == (c % 256))
		{
			temp = cnt;
			isfound = 1;
		}
		cnt++;
	}
	if (*(ptr + cnt) == (c % 256))
		temp = cnt;
	if ((temp == 0 && isfound == 1) || temp > 0)
		return (ptr + temp);
	return (NULL);
}
