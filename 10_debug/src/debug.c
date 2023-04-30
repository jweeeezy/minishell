/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:16:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:30:42 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

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

void	debug_print_pid(char *process_name)
{
	int	pid;

	pid = getpid();
	if (DEBUG)
	{
		printf("%s: pid[%d]\n", process_name, pid);
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

void	debug_stepper(char *message)
{
	ft_putstr_fd(message, 2);
	sleep(2);
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
		printf("\n %s | %s \n, %s \n", delimiter, stage, delimiter);
	}
}
