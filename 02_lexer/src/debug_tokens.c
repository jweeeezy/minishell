/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:02:34 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/13 18:48:11 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

void	debug_tokens(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	printf("\n");
	while (cnt < data->commands_to_process)
	{
		printf("========================\n");
		printf("Combined str: %s\n", data->combine[cnt].combined_str);
		printf("========================\n");
		cnt1 = 0;
		while (cnt1 < data->combine[cnt].count_n)
		{
			printf("Tokens: %s Numb: %i\n",
				data->combine[cnt].execute[cnt1].order_str,
				data->combine[cnt].execute[cnt1].order_numb);
			cnt1++;
		}
		cnt++;
	}
}

void	debug_print_combined(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		printf("%s\n", data->combine[cnt].combined_str);
		cnt++;
	}
}