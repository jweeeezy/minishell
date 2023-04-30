/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:51:18 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 21:31:06 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include <fcntl.h>
#include <stdio.h>

void	debug_print_t_heredoc(t_data *data)
{
	t_heredoc	*index;

	index = data->heredoc;
	if (DEBUG)
	{
		if (index != NULL)
		{
			printf("\nt_heredoc:\n");
			while (index != NULL)
			{
				printf("t_heredoc: node: %p ", index);
				printf("next: %p\n", index->next);
				printf("t_heredoc: full_path: [%s] ", index->full_path);
				printf("hash: [%lu] ", index->hash);
				printf("fd: [%d]\n", index->fd);
				printf("\n");
				index = index->next;
			}
			printf("\n");
		}
		else
		{
			printf("///no heredocs///\n");
		}
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

void	debug_print_t_combine(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (DEBUG)
	{
		printf("t_combine: %p\n", data->combine);
		while (cnt < data->commands_to_process)
		{
			printf("t_combine: combined_str: [%s] order_number: [%i]\n",
				data->combine[cnt].combined_str,
				data->combine[cnt].command->order_numb);
			cnt++;
		}
		printf("\n");
	}
}

void	debug_tokens(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	if (DEBUG)
	{
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
