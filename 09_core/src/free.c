/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/12 16:33:11 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	free_helper(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->tokens && data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
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

void	free_t_heredoc(t_data *data)
{
	t_heredoc 	*current_node;
	t_heredoc	*next_node;

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