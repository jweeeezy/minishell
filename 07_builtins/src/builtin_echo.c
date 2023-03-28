/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/28 23:13:21 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>


void	echo_n(t_data *data, int index)
{
	int		cnt;
	char	*comb;

	comb = NULL;
	cnt = data->combine[index].command->number;
	comb = echo_n_helper(data, cnt, comb);
	if (comb == NULL)
		return (*NULL);
	comb = echo_merge(comb, 0, 0);
	printf("%s", comb);
	free(comb);
}

void	echo(t_combine str)
{
	printf("%s\n", str.combined_str + 5);
}
