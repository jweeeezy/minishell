/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/02 10:36:50 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for access(), NULL
#include "minishell.h"  // needed for t_data, function()
#include "libft.h"      // needed for ft_strjoin()
#include "libme.h"		// needed for ft_str_check_needle()

// for each viable command...
// get envp path variable
// split the evnp path variable?
// search for each split directory if a programm is found
// if yes return found combination (mb in a char * inside the struct)

static char	*executor_get_path_array(char **envp)
{
	char **path_array;

	path_array = NULL;
	while (envp != NULL && *evnp != NULL)
	{
		if (ft_str_check_needle(*envp, "Path=", ft_strlen(*envp)) == 1)
		{
			path_array = ft_split(*envp, ':');
			break ;
		}
		envp += 1;
	}
	return (path_array);
}

static int	*executor_try_access(t_execute *execute, 
		char *path, char *command)
{
	execute->full_path = ft_strjoin(path, command);
	if (execute->full_path == NULL)
		return (ERROR);
	if (access(execute->full_path, F_OK) != -1)
		return (1);
	free(execute->full_path);
	execute->full_path = NULL;
	return (0);
}

static t_executor	*executor_loop_whitespaces(t_execute *execute)
{
	int	index;

	index = 0;
	while (execute[index].order_numb == 1 || execute[index].order_numb == 2)
	{
		index += 1;
	}
	return (execute[index]);
}

static int	executor_check_valid_command(t_data *data, t_execute *offset)
{
	char	**paths;
	int		return_value;

	paths = executor_get_path_array(data->envp);
	if (paths == NULL)
		return (ERROR);
	while (paths != NULL && *paths != NULL)
	{
		return_value = executor_try_access(offset, *paths, offset->order_str);
		if (return_value != 0)
		{
			free_char_array(paths);
			return (return_value);
		}
		paths += 1;
	}
	free_char_array(paths);
	return (0);
}

int	executor_main(t_data *data)
{
	t_execute	*offset;

	offset = executor_loop_whitespaces(data->execute);
	if (offset->order_numb == 10)
	{
		if (executor_try_execve(data, offset) == ERROR)
			return (ERROR);
	}
	return (0);
}
