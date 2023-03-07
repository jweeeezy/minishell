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
		printf(" [%s] ", *args);
		args += 1;
	}
	printf("\n");
}

void	debug_print_t_execute(t_data *data,	t_execute *execute)
{
	int counter;

	counter = 0;
	while (counter < data->tokens)
	{
		printf("t_execute: ");
		printf("order_str: [%s] ", execute[counter].order_str);
		printf("order_numb: [%d] ", execute[counter].order_numb);
		printf("full_path: [%s]\n", execute[counter].full_path);
		counter += 1;
	}
}

void	debug_print_t_expander(t_expander *expander)
{
	printf("t_expander:\n");
	while (expander != NULL)
	{
		printf("[%s]\n", expander->str);
		expander = expander->next;
	}
}
