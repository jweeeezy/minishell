/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/07 10:58:40 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	debug_print_char_array(char **args)
{
	printf("Tokens:");
	while (args != NULL && *args != NULL)
	{
		printf(" {%s} ", *args);
		args += 1;
	}
	printf("\n");
}

void	debug_print_t_execute(t_data *data,
			t_execute *execute)
{
	int counter;

	counter = 0;
	while (counter < data->tokens)
	{
		printf("t_execute: ");
		printf("order_str: [%s] order_numb: [%d]\n", \
			execute[counter].order_str,
				execute[counter].order_numb);
		counter += 1;
	}
}
