/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:57:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/20 19:03:19 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libme.h"
#include "libft.h"
#include <unistd.h>
#include "executor_private.h"

int	try_access(t_execute *execute, char *path, char *command)
{	
	execute->full_path = ft_str_join_delimiter(path, "/", command);
	if (execute->full_path == NULL)
	{
		return (ERROR);
	}
	if (access(execute->full_path, X_OK) == 0)
	{
		return (1);
	}
	free(execute->full_path);
	execute->full_path = NULL;
	return (EXECUTED);
}

int	check_valid_command(t_execute *offset, char **envp)
{	
	int		return_value;
	int		index;
	char	**paths;

	return_value = 0;
	index = 0;
	paths = get_path_array(envp);
	if (paths == NULL)
	{
		return (ERROR);
	}
	while (paths[index] != NULL)
	{
		return_value = try_access(offset, paths[index], offset->order_str);
		if (return_value != 0)
		{
			free_char_array(paths);
			return (return_value);
		}
		index += 1;
	}
	free_char_array(paths);
	return (return_value);
}

int	convert_command_to_vector(t_data *data, t_execute *offset)
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

char	**convert_vector_to_array(t_data *data)
{
	char	**array_command;

	array_command = NULL;
	if (data->vector_args != NULL)
	{
		array_command = ft_split(data->vector_args->str, ' ');
		ft_vector_str_free(data->vector_args);
		data->vector_args = NULL;
	}
	return (array_command);
}
