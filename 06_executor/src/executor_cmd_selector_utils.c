/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_selector_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:11:57 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/13 14:34:49 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// needed for ft_strlen(), ft_split(), ft_strdup()
#include "libme.h"	// needed for ft_str_check_needle(), ft_str_join_delimiter()
#include "minishell.h"	// needed for t_combine
#include "executor.h"	// needed for executor_*()
#include <unistd.h>	// needed for access(), NULL

static char	**selector_get_path_array(char **envp)
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

static int	selector_try_access(t_combine *cmd, char *path, char *command)
{
	cmd->full_path = ft_str_join_delimiter(path, "/", command);
	if (cmd->full_path == NULL)
	{
		return (ERROR);
	}
	if (access(cmd->full_path, X_OK) == 0)
	{
		return (EXTERN);
	}
	free(cmd->full_path);
	cmd->full_path = NULL;
	return (COMMAND_NOT_FOUND);
}

int	selector_is_cmd_path_valid(t_combine *cmd)
{
	char	**array;

	array = ft_split(cmd->combined_str, ' ');
	if (array == NULL)
	{
		return (ERROR);
	}
	if (access(array[0], X_OK) == 0)
	{
		cmd->first_element = ft_strdup(array[0]);
		ft_array_str_free(array);
		return (EXTERN);
	}
	cmd->first_element = ft_strdup(array[0]);
	ft_array_str_free(array);
	return (COMMAND_NOT_FOUND);
}

int	selector_is_cmd_valid(t_combine *cmd, char **envp)
{
	int		return_value;
	char	**paths;
	int		index;

	index = 0;
	paths = selector_get_path_array(envp);
	if (paths == NULL)
	{
		return (ERROR);
	}
	while (paths[index] != NULL)
	{
		return_value = selector_try_access(cmd, paths[index],
				cmd->first_element);
		if (return_value != COMMAND_NOT_FOUND)
		{
			free_char_array(paths);
			return (return_value);
		}
		index += 1;
	}
	free_char_array(paths);
	return (COMMAND_NOT_FOUND);
}