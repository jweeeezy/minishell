/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:28:29 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 21:17:43 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	builtin_env(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (data->envp[cnt] != NULL)
	{
		printf("%s\n", data->envp[cnt]);
		cnt++;
	}
}
