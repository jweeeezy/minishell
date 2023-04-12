/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/12 07:42:45 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process - 1
		&& data->combine[cnt].combined_str != NULL)
	{
		if (data->combine[cnt].combined_str != NULL)
		{
			free(data->combine[cnt].combined_str);
			data->combine[cnt].combined_str = NULL;
		}
		cnt++;
	}
	free(data->line);
	if (data->commands_to_process - 1 > 0)
		free(data->combine);
}

void	free_char_array(char **array_to_free)
{
	int	index;

	index = 0;
	while (array_to_free != NULL && array_to_free[index] != NULL)
	{
		free (array_to_free[index]);
		index += 1;
	}
	free (array_to_free);
}

void	free_pipe_array(int **array, int size)
{
	int	index;

	index = 0;
	while (index < size && array[index] != NULL)
	{
		free(array[index]);
		index += 1;
	}
	free(array);
}
