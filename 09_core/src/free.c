/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/17 19:25:16 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	free_helper(t_data *data)
{
	if (data->commands_to_process > 0)
	{
		free(data->combine);
		data->combine = NULL;
	}
	if (data->line != NULL)
		free(data->line);
	data->line = NULL;
}

void	free_tokens(t_data *data, int cnt)
{
	int	cnt1;

	cnt1 = 0;
	while (cnt1 < data->combine[cnt].count_n)
	{
		if (data->combine[cnt].execute[cnt1].order_str != NULL)
		{
			free(data->combine[cnt].execute[cnt1].order_str);
			data->combine[cnt].execute[cnt1].order_str = NULL;
		}
		cnt1++;
	}
}

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (data->line == NULL || *data->line == '\0')
	{
		free(data->line);
		data->line = NULL;
		return ;
	}
	while (cnt < data->commands_to_process)
	{
		free_tokens(data, cnt);
		if (data->combine[cnt].combined_str != NULL)
		{
			free(data->combine[cnt].combined_str);
			data->combine[cnt].combined_str = NULL;
			free(data->combine[cnt].execute);
			data->combine[cnt].execute = NULL;
		}
		cnt++;
	}
	free_helper(data);
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

void	free_t_heredoc(t_data *data)
{
	t_heredoc	*current_node;
	t_heredoc	*next_node;

	if (data->flag_heredoc == 1)
	{
		unlink(data->heredoc->full_path);
		free(data->heredoc->full_path);
		free(data->heredoc);
		data->heredoc = NULL;
		data->flag_heredoc = 0;
		return ;
	}
	current_node = data->heredoc;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->full_path);
		free(current_node);
		current_node = next_node;
	}
	data->heredoc = NULL;
}
