/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/09 19:54:39 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for fork(), access(), NULL
#include "minishell.h"  // needed for t_data, function()
#include "libft.h"      // needed for ft_strjoin()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter(), t_vector_str

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
	if (access(execute->full_path, F_OK) != -1)
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
		return (NULL);
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
		return (ERROR);
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
	int	id;

	id = fork();
	if (id == -1)
	{
		return (ERROR);
	}
	if (id == 0)
	{
		execve(offset->full_path, NULL, data->envp);
	}
	else
	{
		if (wait(NULL) == -1)
			return (ERROR);
	}
	return (0);
}

static int	executor_get_command_arguments(t_data *data, t_execute *offset)
{
	t_vector_str	*vector_args;

	vector_args = data->vector_args;
	while (offset != NULL && offset->order_numb != 5)
	{
		vector_args = ft_vector_str_join(vector_args, offset->order_str, 0);
		if (vector_args == NULL)
		{
			return (ERROR);
		}
		offset += 1;
	}
	if (DEBUG)
	{
		debug_print_t_vector_str(data->vector_args);
	}
	return (0);
}

int	executor_main(t_data *data)
{
	t_execute	*offset;
	int			return_value;

	return_value = 0;
	offset = executor_loop_whitespaces(data->execute);
	if (offset == NULL)
		return (ERROR);
	if (offset->order_numb == 10)
	{
		return_value = executor_check_valid_command(data, offset);
		if (return_value == 1)
		{
			if ((offset + 1)->order_str != NULL)
			{
				if (executor_get_command_arguments(data, offset + 1) == ERROR)
				{
					return (ERROR);
				}
			}
			executor_try_execve(data, offset);
		}
		else if (return_value == ERROR)
		{
			return (ERROR);
		}
	}
	return (0);
}
