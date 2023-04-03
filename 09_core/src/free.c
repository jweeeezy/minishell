/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 21:58:21 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	free_tks(t_data *data, int cnt)
{
	int	cnt1;

	cnt1 = 0;
	while (cnt1 < data->combine[cnt].tks
		&& data->combine[cnt].order_str != NULL)
	{
		free(data->combine[cnt].order_str[cnt1]);
		data->combine[cnt].order_str[cnt1] = NULL;
		cnt++;
	}
	data->combine[cnt].tks = 0;
}

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
		free_tks(data, cnt);
		if (data->combine[cnt].order_str != NULL)
		{
			free(data->combine[cnt].order_str);
			data->combine[cnt].order_str = NULL;
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
