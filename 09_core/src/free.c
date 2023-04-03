/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 13:32:56 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	free_helper(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->tokens && data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
		data->args[cnt] = NULL;
		free(data->execute[cnt].order_str);
		data->execute[cnt].order_str = NULL;
		free(data->execute[cnt].full_path);
		data->execute[cnt].full_path = NULL;
		data->execute[cnt].order_numb = 0;
		cnt++;
	}
}

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (data->line != NULL)
		free_helper(data);
	free(data->line);
	while (cnt < data->commands_to_process
		&& data->combine[cnt].combined_str != NULL)
	{
		free(data->combine[cnt].combined_str);
		data->combine[cnt].combined_str = NULL;
		cnt++;
	}
	if (data->tokens > 0)
	{
		free(data->execute);
		free(data->args);
	}
	if (data->commands_to_process > 0 && data->combine != NULL)
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
