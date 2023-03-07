/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/07 10:16:25 by jwillert         ###   ########.fr       */
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

void	debug_print_t_execute(t_execute *execute)
{
	printf("t_execute:");
	printf("order_str: [%s] order_numb: [%d]\n", \
			execute->order_str, execute->order_numb);
}
