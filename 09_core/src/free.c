/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 19:39:43 by jwillert         ###   ########.fr       */
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
			if (data->combine[cnt].combined_str != NULL)
				free(data->combine[cnt].combined_str);
			data->combine[cnt].combined_str = NULL;
			if ((data->combine[cnt].execute) != NULL)
				free(data->combine[cnt].execute);
			data->combine[cnt].execute = NULL;
		}
		cnt++;
	}
	free_helper(data);
}

void	free_child(t_data *data, int **fd_pipes, int index)
{
	free_pipe_array(fd_pipes, data->counter_pipes);
	if (data->heredoc != NULL)
		free_t_heredoc(data);
	if (data->combine[index].full_path != NULL)
		free(data->combine[index].full_path);
	free(data->child_pids);
	free_env(data);
	free_loop(data);
}
