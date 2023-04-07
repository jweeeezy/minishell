/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/30 10:49:30 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"    

int	count_split(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	split_free(char **split)
{
	int	cnt;

	cnt = 0;
	while (split[cnt] != NULL)
	{
		free(split[cnt]);
		cnt++;
	}
	free(split);
}
