/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/14 11:12:57 by jwillert         ###   ########          */
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
		dup2(fd_pipe[0], STDOUT_FILENO);
	}
	if (execve(offset->full_path, array_command, data->envp) == -1)
	{
		//@note needed?
		free_char_array(array_command);
		perror("execve");
		exit (ERROR);
	}
}

int	execute_in_child(t_data *data, t_execute *offset,
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
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
		}
		if (wait(NULL) == -1)
		{
			return (ERROR);
		}
	}
	// @note freeing setting to NULL
	free_char_array(array_command);
	return (EXECUTED);
}

static int	executor_pipe(t_data *data, t_execute *offset,
	   			t_execute *next_pipe, int *fd_pipe)
{
	pid = fork();
	if (pid == -1)
	{
		return (ERROR);
	}
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		if (execve(offset->full_path, arg_array, data->envp) == -1)
		{
			perror("execve");
		}
		exit(ERROR);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			return (ERROR);
		}
		else if (pid == 0)
		{
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			ft_vector_str_free(data->vector_args);
			data->vector_args = NULL;
			offset = executor_t_execute_advance_offset(offset, next_pipe);
			if (executor_check_valid_command(data, offset) != 1)
			{
				exit(ERROR);
			}
			executor_get_command_arguments(data, offset);
			free_char_array(arg_array);
			if (data->vector_args != NULL)
				arg_array = ft_split(data->vector_args->str, ' ');
			else
			{
				arg_array = NULL;
			}
			ft_vector_str_free(data->vector_args);
			data->vector_args = NULL;
			if (execve(offset->full_path, arg_array, data->envp) == -1)
			{
				perror("execve");
			}
			exit(ERROR);
		}
		else
		{
			close(fd_pipe[0]);
			wait(NULL);
		}
		close(fd_pipe[1]);
		wait(NULL);
	}
	ft_vector_str_free(data->vector_args);
	data->vector_args = NULL;
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	t_execute	*offset;
	t_execute	*next_pipe;
	int			return_value;
	int			counter_pipes;
	int			fd_pipe[2];
	int			fd_stdin;
	int			fd_stdout;

	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);

	return_value = 0;
	counter_pipes = 0;

	pipe(fd_pipe);
	// @note mb parsing will loop through white spaces already?
	offset = executor_loop_whitespaces(data->execute);
	// @note mb while loop so it goes until no pipe is left, but it should also
	// advance the offset to the next order_numb == STRING
	if (offset == NULL)
	{
		return (ERROR);
	}
	counter_pipes = count_pipes(offset);
	debug_print_int("Counter pipes: ", counter_pipes);

	while (counter_pipes > 1)
	{
		
		printf("Reached\n");
		next_pipe = executor_t_execute_get_pipe(offset);
		if (next_pipe->order_str != NULL)
		{
			return_value = executor_check_valid_command(data, offset);
			if (return_value == 1)
			{
				if (executor_get_command_arguments(data, offset) == ERROR)
				{
					return (ERROR);
				}
				else if (next_pipe->order_numb == PIPE)
				{
					dup2(fd_pipe[0], STDIN_FILENO);
					dup2(fd_pipe[1], STDOUT_FILENO);
					if (executor_pipe(data, offset, next_pipe, fd_pipe) == ERROR)
					{
						return (ERROR);
					}
				}
			}
		}
		counter_pipes -= 1;
		offset = next_pipe + 1;
		offset = executor_loop_whitespaces(offset);
	}
	if (counter_pipes == 1)
	{
		printf("Reached 2\n");
		next_pipe = executor_t_execute_get_pipe(offset);
		if (next_pipe->order_str != NULL)
		{
			return_value = executor_check_valid_command(data, offset);
			if (return_value == 1)
			{
				if (executor_get_command_arguments(data, offset) == ERROR)
				{
					return (ERROR);
				}
				if (next_pipe->order_numb == PIPE)
				{
					if (executor_pipe(data, offset,
								next_pipe, fd_pipe) == ERROR)
					{
						return (ERROR);
					}
				}
			}
		}
	}
	else if (offset->order_numb == STRING)
	{
		// @todo extract code as execute extern command
		printf("Reached 3\n");
		return_value = executor_check_valid_command(data, offset);
		if (return_value == 1)
		{
			if (executor_get_command_arguments(data, offset) == ERROR)
			{
				return (ERROR);
			}
			if (executor_try_execve(data, offset) == ERROR)
			{
				return (ERROR);
			}
		}
		//	@note can prob save this part and just return return_value
		else if (return_value == ERROR)
		{
			return (ERROR);
		}
	}
	return (0);
}
