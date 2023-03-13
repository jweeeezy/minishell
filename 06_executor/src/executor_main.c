/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/13 11:16:18 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for fork(), access(), NULL
#include "minishell.h"  // needed for t_data, function()
#include "libft.h"      // needed for ft_strjoin()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter(), t_vector_str
#include <stdio.h>		// needed for perror()

//	@todo Refactor code into multiple files

static char	**executor_get_path_array(char **envp)
{
	char	**path_array;

	path_array = NULL;
	while (envp != NULL && *envp != NULL)
	{
		if (ft_str_check_needle(*envp, "PATH=", ft_strlen(*envp)) == 1)
		{
			path_array = ft_split(*envp + 5, ':');
			break ;
		}
		envp += 1;
	}
	return (path_array);
}

static int	executor_try_access(t_execute *execute,
				char *path, char *command)
{
	execute->full_path = ft_str_join_delimiter(path, "/", command);
	if (execute->full_path == NULL)
	{
		return (ERROR);
	}
	if (access(execute->full_path, X_OK) != -1)
	{
		return (1);
	}
	free(execute->full_path);
	execute->full_path = NULL;
	return (0);
}

static t_execute	*executor_loop_whitespaces(t_execute *execute)
{
	int	index;

	index = 0;
	if (execute == NULL)
	{
		return (NULL);
	}
	while (execute[index].order_numb == 1 || execute[index].order_numb == 2)
	{
		index += 1;
	}
	return (&execute[index]);
}

static int	executor_check_valid_command(t_data *data, t_execute *offset)
{
	char	**paths;
	int		return_value;
	int		index;

	index = 0;
	paths = executor_get_path_array(data->envp);
	if (paths == NULL)
	{
		return (ERROR);
	}
	while (paths[index] != NULL)
	{
		return_value = executor_try_access(offset, paths[index],
				offset->order_str);
		if (return_value != 0)
		{
			free_char_array(paths);
			return (return_value);
		}
		index += 1;
	}
	free_char_array(paths);
	return (0);
}

static int	executor_try_execve(t_data *data, t_execute *offset)
{
	char	**arg_array;	
	int		id;

	//@todo check if this is needed
	if (data->vector_args != NULL)
	{
		arg_array = ft_split(data->vector_args->str, ' ');
		if (arg_array == NULL)
		{
			ft_vector_str_free(data->vector_args);
			return (ERROR);
		}
	}
	else
	{
		arg_array = NULL;
	}
	id = fork();
	if (id == -1)
	{
		return (ERROR);
	}
	if (id == 0)
	{
		// @todo extract code as child_routine
		debug_print_char_array(arg_array);
		if (execve(offset->full_path, arg_array,
			data->envp) == -1)
		{
			perror("execve");
		}
		exit(ERROR);
	}
	else
	{
		if (wait(NULL) == -1)
		{
			free_char_array(arg_array);
			return (ERROR);
		}
		free_char_array(arg_array);
	}
	return (0);
}

static int	executor_get_command_arguments(t_data *data, t_execute *offset)
{
	t_vector_str	*vector_args;

	vector_args = data->vector_args;
	while (offset->order_str != NULL && offset->order_numb != 5)
	{
		vector_args = ft_vector_str_join(vector_args, offset->order_str, 0);
		if (vector_args == NULL)
		{
			return (ERROR);
		}
		offset += 1;
	}
	data->vector_args = vector_args;
	debug_print_t_vector_str(data->vector_args);
	return (0);
}

static t_execute	*executor_t_execute_get_pipe(t_execute *offset)
{
	int	index;

	index = 0;
	while (offset[index].order_str != NULL
			&& offset[index].order_numb != PIPE)
	{
		index += 1;
	}
	return (&offset[index]);
}

static t_execute *executor_t_execute_advance_offset(t_execute *offset,
			t_execute *next_pipe)
{
	int	index;
	
	index = 0;
	while (&offset[index] != next_pipe
			&& offset[index].order_str != NULL)
	{
		index += 1;
	}
	while (offset[index].order_numb != STRING
			&& offset[index].order_str != NULL)
	{
		index += 1;
	}
	return (&offset[index]);
}

static int	executor_pipe(t_data *data, t_execute *offset, t_execute *next_pipe)
{
	int		fd_pipe[2];
	pid_t	pid;
	char	**arg_array;
	int		fd_stdout;
	int		fd_stdin;

	fd_stdout = dup(STDOUT_FILENO);
	fd_stdin = dup(STDIN_FILENO);

	if (data->vector_args != NULL)
	{
		arg_array = ft_split(data->vector_args->str, ' ');
		if (arg_array == NULL)
		{
			ft_vector_str_free(data->vector_args);
			return (ERROR);
		}
	}
	else
	{
		arg_array = NULL;
	}
	if (pipe(fd_pipe) == -1)
	{
		return (ERROR);
	}
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
	dup2(fd_stdout, STDOUT_FILENO);
	dup2(fd_stdin, STDIN_FILENO);
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	t_execute	*offset;
	t_execute	*next_pipe;
	int			return_value;

	return_value = 0;
	// @note mb parsing will loop through white spaces already?
	offset = executor_loop_whitespaces(data->execute);
	// @note mb while loop so it goes until no pipe is left, but it should also
	// advance the offset to the next order_numb == STRING
	if (offset == NULL)
	{
		return (ERROR);
	}
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
			if (executor_pipe(data, offset, next_pipe) == ERROR)
			{
				return (ERROR);
			}
		}
	}
	else if (offset->order_numb == STRING)
	{
		// @todo extract code as execute extern command
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
