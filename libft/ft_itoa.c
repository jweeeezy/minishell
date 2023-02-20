/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:16:36 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 17:20:00 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int C)
{
	int	size;

	size = 0;
	if (C < 0)
	{
		size++;
		C = (-1) * C;
	}
	if (C == 0)
		return (1);
	while (C >= 1)
	{
		C = C / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		s_holder;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s_holder = ft_size(n);
	dest = ft_calloc((s_holder + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{	
		*dest = '-';
		n = -1 * n;
	}	
	if (n == 0)
		*dest = '0';
	while (n != 0)
	{
		*(dest + s_holder - 1) = n % 10 + 48;
		n = n / 10;
		s_holder --;
	}
	return (dest);
}
