/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:39:35 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 19:35:15 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	free_env(t_data *data)
{
	int	cnt;

	cnt = 0;
	if (data->envp != NULL)
	{
		while (data->envp[cnt] != NULL)
		{
			free(data->envp[cnt]);
			data->envp[cnt] = NULL;
			cnt++;
		}
		free(data->envp);
		data->envp = NULL;
	}
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
