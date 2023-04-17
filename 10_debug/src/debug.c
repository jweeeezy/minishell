/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/18 00:24:58 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>			// needed for printf(), NULL
#include "minishell.h"		// needed for t_data

void	debug_print_char_array(char **args, char *name)
{
	if (DEBUG)
	{
		printf("%s: %p\n", name, args);
		while (args != NULL && *args != NULL)
		{
			printf("%s: [%s]\n", name, *args);
			args += 1;
		}
		printf("\n");
	}
}

void	debug_print_t_execute(t_data *data,	t_execute *execute)
{
	int	counter;

	counter = 0;
	if (DEBUG)
	{
		printf("t_execute: %p\n", execute);
		while (counter < data->tokens + 1 && execute[counter].order_str != NULL)
		{
			printf("t_execute: ");
			printf("order_str: [%s] ", execute[counter].order_str);
			printf("order_numb: [%d]", execute[counter].order_numb);
			printf("\n");
			counter += 1;
		}
		printf("\n");
	}
}

void	debug_print_int(char *description, int int_to_print)
{
	if (DEBUG)
	{
		printf("%s: %p\n", description, &int_to_print);
		printf("%s: %d\n", description, int_to_print);
		printf("\n");
	}
}
