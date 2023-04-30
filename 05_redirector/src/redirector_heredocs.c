/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:00:50 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>				// needed for close(), fork()
#include "redirector.h"			// needed for heredoc_lst_update(),
								// heredoc_child_routine()
#include "minishell.h"			// needed for t_data, MACROS

static int	count_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;

	index = 0;
	counter_heredocs = 0;
	while (index < data->commands_to_process)
	{
		if (data->combine[index].command->order_numb == HERE_DOC
			|| data->combine[index].command->order_numb == QUOTED_HEREDOC)
		{
			counter_heredocs += 1;
		}
		index += 1;
	}
	return (counter_heredocs);
}

static int	heredoc_fork_and_open(t_data *data, int index, int id, int status)
{
	t_heredoc	*current_node;

	current_node = heredoc_lst_update(data);
	if (current_node == NULL)
		return (ERROR);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		heredoc_child_routine(data, index, current_node, status);
	}
	else
	{
		wait(&status);
		close(current_node->fd);
	}
	if (status == 512)
		return (-2);
	return (EXECUTED);
}

int	redirector_prehandle_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;
	int	status;

	index = 0;
	counter_heredocs = count_heredocs(data);
	while (index < data->commands_to_process && counter_heredocs > 0)
	{
		if (data->combine[index].command->order_numb == HERE_DOC
			|| data->combine[index].command->order_numb == QUOTED_HEREDOC)
		{
			status = heredoc_fork_and_open(data, index, 0, 0);
			if (status == ERROR)
				return (ERROR);
			else if (status == -2)
				return (-2);
			counter_heredocs -= 1;
		}
		index += 1;
	}
	return (EXECUTED);
}
