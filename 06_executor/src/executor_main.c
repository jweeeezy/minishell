/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/22 10:54:21 by kvebers          ###   ########.fr       */
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
		free_char_array(array_command);
		perror("execve");
		exit(ERROR);
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
		return (ERROR);
	return (0);
}

static int	execute_in_child(t_data *data, t_execute *offset,
		char **array_command, int *fd_pipe)
{
	int	id;

	id = fork();
	if (id == ERROR)
		return (ERROR);
	if (id == 0)
		child_routine(data, offset, array_command, fd_pipe);
	else
	{
		if (parent_routine(fd_pipe) == -1)
			return (ERROR);
	}
	free_char_array(array_command);
	return (EXECUTED);
}

static int	executor_routine(t_data *data, t_combine *cmd, int *fd_pipe)
{
	int			return_value;
	char		**array_command;

	return_value = check_valid_command(cmd->command, data->envp);
	if (return_value == 1)
	{
		array_command = convert_str_to_array(cmd);
		if (array_command == NULL)
			return (ERROR);
		if (execute_in_child(data, cmd->command,
				array_command, fd_pipe) == ERROR)
			return (ERROR);
	}
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	int			counter_pipes;
	int			fd_pipe[2];
	t_execute	*next_pipe;

	if (pipe(fd_pipe) == ERROR)
		return (ERROR);
	counter_pipes = count_pipes(data);
	while (counter_pipes > 0)
	{
		next_pipe = get_pipe(data->combine->command);
		if (next_pipe->order_str != NULL)
		{
			if (executor_routine(data, data->combine, fd_pipe) == ERROR)
				return (ERROR);
		}
		data->combine += 1;
		counter_pipes--;
	}
	if (data->tokens > 0)
		if (executor_routine(data, data->combine, NULL) == ERROR)
			return (ERROR);
	return (0);
}
