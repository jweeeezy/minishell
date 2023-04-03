/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_usless_quotes1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:38:22 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 10:26:46 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

char	*remove_usless_quotes5(char *str, int *numb, int cnt)
{
	char	*temp;

	temp = NULL;
	while (str[cnt] != '\0')
	{
		if (numb[cnt] != 3)
			temp = ft_charjoin(temp, str[cnt], 0, 0);
		cnt++;
	}
	return (free(str), temp);
}
