/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:29:23 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 21:56:14 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

void	init_tokens(t_data *data, int cnt1)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->combine[cnt1].tks)
	{
		data->combine[cnt1].order_str[cnt] = NULL;
		cnt++;
	}
}

void	init_combine(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		data->combine[cnt].count_n = cnt;
		data->combine[cnt].combined_str = NULL;
		cnt++;
	}
	data->combine[cnt].combined_str = NULL;
}
