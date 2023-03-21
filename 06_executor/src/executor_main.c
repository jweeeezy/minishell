/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/21 10:35:04 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for fork(), access(), NULL
#include "minishell.h"  // needed for t_data, function()
#include "executor_private.h"
#include <stdio.h>		// needed for perror()
						//
static void	child_routine(t_data *data, t_execute *offset,
		char **array_command, int *fd_pipe)
{
	if (fd_pipe != NULL)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	if (execve(offset->full_path, array_command, data->envp) == -1)
	{
		//@note freeing in child needed?
		free_char_array(array_command);
		perror("execve");
	}
}

static int	parent_routine(int *fd_pipe)
{
	if (fd_pipe != NULL)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
	}
	if (wait(NULL) == -1)
	{
		return (ERROR);
	}
	return (0);
}

static int	execute_in_child(t_data *data, t_execute *offset,
		char **array_command, int *fd_pipe)
{
	int	id;

	id = fork();
	if (id == ERROR)
	{
		return (ERROR);
	}
	if (id == 0)
	{
		child_routine(data, offset, array_command, fd_pipe);
	}
	else
	{
		if (parent_routine(fd_pipe) == -1)
		{
			return (ERROR);
		}
	}
	free_char_array(array_command);
	return (EXECUTED);
}

static int	executor_routine(t_data *data, t_execute *offset, int *fd_pipe)
{
	int			return_value;
	char		**array_command;

	return_value = check_valid_command(offset, data->envp);
	if (return_value == 1)
	{
		if (convert_command_to_vector(data, offset) == ERROR)
		{
			return (ERROR);
		}
		array_command = convert_vector_to_array(data);
		if (array_command == NULL)
		{
			return (ERROR);
		}
		if (execute_in_child(data, offset, array_command, fd_pipe) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	int			counter_pipes;
	int			fd_pipe[2];
	t_execute	*next_pipe;
	t_execute	*offset;

	if (pipe(fd_pipe) == ERROR)
	{
		return (ERROR);
	}
	offset = get_string_after_whitespaces(data->execute);
	counter_pipes = count_pipes(offset);
	if (offset == NULL)
	{
		return (ERROR);
	}
	while (counter_pipes > 0)
	{
		next_pipe = get_pipe(offset);
		if (next_pipe->order_str != NULL)
		{
			if (executor_routine(data, offset, fd_pipe) == ERROR)
			{
				printf("here\n");
				return (ERROR);
			}
		}
		offset = get_string_after_pipe(offset, next_pipe);
		counter_pipes -= 1;
	}
	if (executor_routine(data, offset, NULL) == ERROR)
	{
		return (ERROR);
	}
	return (0);
}
