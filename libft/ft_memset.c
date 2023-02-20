/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:11:30 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 16:45:36 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{	
	size_t	cnt;
	char	*b_char;

	b_char = (char *)b;
	cnt = 0;
	while (cnt < len)
	{
		*(b_char + cnt) = c;
		cnt++;
	}
	return (b_char);
}
