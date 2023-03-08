/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/08 16:26:36 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	echo(t_data *data, int cnt)
{
	int	quotes;
	int	new_line;

	new_line = 0;
	quotes = 0;
	cnt++;
	if (data->string != NULL)
	{
		free(data->string);
		data->string = NULL;
	}
	if (data->execute[cnt].order_str == NULL
		|| is_pipe(data->execute[cnt].order_numb) == 1)
	{
		data->string = ft_strdup("\n");
		return ;
	}
	while (data->execute[cnt].order_numb == WHITE && cnt < data->tokens
		&& is_pipe(data->execute[cnt].order_numb) != ADD)
	cnt++;
	if (ft_strncmp(data->execute[cnt].order_str, "-n", 2) == 0
		&& ft_strlen(data->execute[cnt].order_str) == 2)
		new_line = 1;
	cnt++;
}
