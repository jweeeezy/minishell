/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/28 14:01:01 by jwillert         ###   ########.fr       */
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

void	debug_print_redirections(t_data *data)
{
	if (DEBUG)
	{
		if (data->flag_heredoc == 1 || data->flag_infile == 1 || data->flag_outfile == 1)
		{
			printf("redirections: \n");
			printf("redirections: flag_heredoc: [%d] ", data->flag_heredoc);
			printf("flag_infile: [%d] ", data->flag_infile);
			printf("flag_outfile: [%d]\n", data->flag_outfile);
			printf("redirections: fd_infile: [%d] ", data->fd_infile);
			printf("                    fd_outfile: [%d]\n",
				data->fd_outfile);
		}
		else
		{
			//printf("///no redirections///\n");
			return ;
		}
		printf("\n");
	}
}

void	debug_print_stage(char *stage, int level)
{
	char	*delimiter;

	delimiter = NULL;
	if (DEBUG)
	{
		if (level == 0)
		{
			delimiter = "********************\n";
		}
		else if (level == 1)
		{
			delimiter = "------------\n";
		}
		else if (level == 2)
		{
			delimiter = "~~~\n";
		}
		else
		{
			return ;
		}
		printf("\n");
		printf("%s", delimiter);
		printf("| %s \n", stage);
		printf("%s", delimiter);
		printf("\n");
	}
}
