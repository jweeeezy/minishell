/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:02:34 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 22:55:12 by kvebers          ###   ########.fr       */
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
		while (cnt1 < data->combine[cnt].tks)
		{
			printf("Tokens: %s\n", data->combine[cnt].order_str[cnt1]);
			cnt1++;
		}
		cnt++;
	}
}

void	print_numberator(char *str, int *numb, int *numb1)
{
	int	cnt;

	cnt = 0;
	printf("=============\n");
	while (str[cnt] != '\0')
	{
		printf("%i %i %c\n", numb[cnt], numb1[cnt], str[cnt]);
		cnt++;
	}
	printf("=============\n");
}
