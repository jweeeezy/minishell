/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:47:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/14 13:35:25 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor.h"	// needed for utils_is
#include <unistd.h>				// needed for pipe()

int	pipex_advance_to_next_pipe(t_data *data, int index)
{
	index += 1;
	while (data->combine[index].combined_str != NULL
		   && data->combine[index].command->order_numb != PIPE
		   && data->combine[index].command->order_numb != LAST_PIPE)
	{
		index += 1;
	}
	return (index);
}

static int	**pipex_create_pipes(int counter_pipes)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = malloc (sizeof (int *) * (counter_pipes + 1));
	if (fd_pipes == NULL)
	{
		return (NULL);
	}
	while (index < counter_pipes)
	{
		fd_pipes[index] = malloc (sizeof (int) * 2);
		if (fd_pipes[index] == NULL
			|| pipe(fd_pipes[index]) == ERROR)
		{
			free_pipe_array(fd_pipes, index);
			return (NULL);
		}
		index += 1;
	}
	fd_pipes[counter_pipes] = NULL;
	return (fd_pipes);
}

int	pipex_skip_non_commands(t_data *data, int index)
{
	while ((data->combine[index].combined_str != NULL
			&& data->combine[index].command->order_numb != STRING
			&& is_builtin(data->combine[index].command->order_numb) == 0))
	{
		index += 1;
	}
	return (index);
}

int	executor_pipex(t_data *data)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = pipex_create_pipes(data->counter_pipes);
	if (fd_pipes == NULL)
	{
		return (ERROR);
	}
	while (index < data->commands_to_process)
	{
		// advance until string or pipe
		//  if pipe and no string
		//  	--> no command found?
		//  return index!

		//
		debug_print_t_combine(data);
		if (executor_cmd_selector(data, fd_pipes, index) == ERROR)
		{
			free_pipe_array(fd_pipes, data->counter_pipes);
			return (ERROR);
		}
		index = pipex_advance_to_next_pipe(data, index);
		data->index_processes += 1;
	}
	free_pipe_array(fd_pipes, data->counter_pipes);
	return (EXECUTED);
}
