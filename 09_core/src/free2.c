/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:39:35 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 14:20:53 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

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

void	free_child_pids(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->counter_processes)
	{
		free(&data->child_pids[index]);
		index += 1;
	}
	free(data->child_pids);
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