/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:06:41 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 18:15:38 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL || f == NULL)
		return ;
	while (*(s + cnt) != '\0')
	{
		(f)(cnt, s + cnt);
		cnt++;
	}
}
