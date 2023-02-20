/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:12:53 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/02 23:11:31 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long			output;
	long			sign;
	unsigned long	c;

	sign = 1;
	c = 0;
	output = 0;
	while ((*(str + c) >= 9 && *(str + c) <= 13) || *(str + c) == ' ')
		c++;
	if (*(str + c) == '+' || *(str + c) == '-')
	{
		if (*(str + c) == '-')
			sign = (-1);
		c++;
	}
	while (*(str + c) != '\0')
	{
		if (*(str + c) < '0' || *(str + c) > '9')
			break ;
		output = output * 10 + (*(str + c) - '0');
		c++;
	}
	return (output * sign);
}
