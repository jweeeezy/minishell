/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:36:25 by kvebers           #+#    #+#             */
/*   Updated: 2022/12/06 11:50:27 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printhex(unsigned long C, int up_low)
{
	if (C % 16 < 10)
		ft_putchar_fd((C % 16 + 48), 1);
	if (C % 16 > 9)
		ft_putchar_fd(C % 16 + up_low, 1);
}

int	ft_puthex(unsigned long C, int up_low)
{
	int	cnt;

	cnt = 1;
	if (C == 0)
		ft_putchar_fd('0', 1);
	else if (C < 16)
		ft_printhex(C, up_low);
	else if (C > 15)
	{
		cnt = cnt + ft_puthex(C / 16, up_low);
		ft_printhex(C, up_low);
	}
	return (cnt);
}
