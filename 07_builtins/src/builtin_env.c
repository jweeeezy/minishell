/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:28:29 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/27 15:51:39 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	env(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (data->envp[cnt] != NULL)
	{
		printf("%s\n", data->envp[cnt]);
		cnt++;
	}
}
