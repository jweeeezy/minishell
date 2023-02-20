/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:29:37 by kvebers           #+#    #+#             */
/*   Updated: 2022/12/06 11:50:45 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsigned(unsigned long C)
{
	unsigned int	cnt;

	cnt = 1;
	if (C == 0)
		ft_putchar_fd('0', 1);
	else if (C < 10)
		ft_putchar_fd(C + 48, 1);
	else if (C > 9)
	{
		cnt = cnt + ft_putunsigned(C / 10);
		ft_putchar_fd(C % 10 + 48, 1);
	}
	return (cnt);
}
