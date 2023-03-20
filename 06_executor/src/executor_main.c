/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/20 11:13:33 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for fork(), access(), NULL
#include "minishell.h"  // needed for t_data, function()
#include "libft.h"      // needed for ft_strjoin()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter(), t_vector_str
#include <stdio.h>		// needed for perror()

//	@todo Refactor code into multiple files

static void	child_routine(t_data *data, t_execute *offset,
		char **array_command, int *fd_pipe)
{
	debug_print_char_array(array_command);
	if (fd_pipe != NULL)
	{
		close(fd_pipe[1]);
	}
	if (execve(offset->full_path, array_command, data->envp) == -1)
	{
		//@note freeing in child needed?
		free_char_array(array_command);
		perror("execve");
		exit (ERROR);
	}
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
		if (fd_pipe != NULL)
		{
			close(fd_pipe[0]);
		}
		if (wait(NULL) == -1)
		{
			return (ERROR);
		}
	}
	// @note freeing setting to NULL
	close(fd_pipe[1]);
	free_char_array(array_command);
	return (EXECUTED);
}


static int	executor_routine(t_data *data, t_execute *offset,
		t_execute *next_pipe, int *fd_pipe)
{
	int			return_value;
	char		**array_command;

	return_value = 0;
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
	return (return_value);
}

int	executor_main(t_data *data)
{
	int			counter_pipes;
	int			fd_pipe[2];
	int			fd_stdin;
	int			fd_stdout;
	t_execute	*next_pipe;
	t_execute	*offset;

	if (pipe(fd_pipe) == ERROR)
	{
		return (ERROR);
	}
	offset = executor_loop_whitespaces(data->execute);
	counter_pipes = count_pipes(offset);
	if (offset == NULL)
	{
		return (ERROR);
	}
	
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);

	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);

	while (counter_pipes > 0)
	{
		next_pipe = get_pipe(offset);
		if (next_pipe->order_str != NULL)
		{
			if (executor_routine(data, offset, next_pipe, fd_pipe) == ERROR)
			{
				return (ERROR);
			}
		}
	}

	dup2(STDIN_FILENO, ft_stdin);
	dup2(STDOUT_FILENO, ft_stdout);
	if (executor_routine(data, offset, next_pipe, fd_pipe) == ERROR)
	{
		return (ERROR);
	}
}

