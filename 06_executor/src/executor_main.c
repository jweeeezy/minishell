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

static int executor_get_path_array(char **envp)
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

static char *executor_loop_through_paths(char **paths, char *command)
{
	int	return_value;

	return_value = 0;
	while (paths != NULL && *paths != NULL)
	{
		return_value = executor_check_path_and_command(*path, command);
		if (return_value == NULL);
			return (NULL);
		else if (return_value == 1);
			return (*path);
			
		if (access()
			return (1);
		paths += 1;
	}
	return (return_value);
}

static int	executor_check_path_and_command(char *path, char *command)
{
	char	*str_combined;
	int		return_value;
	
	return_value = 0;
	str_combined = ft_strjoin(path, command);
	if (str_combines == NULL)
		return (ERROR);
	if (access(str_combined, F_OK != -1)
		return (str_combined);
	free(str_combined);
	return (NULL);
}





static int	executor_check_path(char *path_to_check)
{





	return (0);
}





int	executor_main(t_data *data)
{
	int		id;
	char	*path;
	char	*command;

	command = data->execute->order_str;
	// if its valid path
		path = command;
	// if its not valid path
		path = ft_strjoin("/bin/", command);
	id = fork();
	if (id == -1)
	{
		return (-1);
	}
	if (id == 0)
	{
		return (execve(path, data->args, data->envp));
	}
	else
	{
		if (wait(NULL) == -1)
			return (-1);
	}
	return(0);
}
