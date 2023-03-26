/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_extern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:10:36 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/26 17:05:01 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS, free_()
#include "executor_private.h"	// needed for child(), parent(); 
#include "libft.h"		// needed for ft_strlen(), ft_split()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter()
#include <unistd.h>		// needed for NULL, access(), malloc(), free()
#include <stdio.h>		// needed for printf(); @note prob not needed

static char	**extern_get_path_array(char **envp)
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

static int	extern_try_access(t_execute *cmd, char *path, char *command)
{
	cmd->full_path = ft_str_join_delimiter(path, "/", command);
	if (cmd->full_path == NULL)
		return (ERROR);
	if (access(cmd->full_path, X_OK) == 0)
		return (1);
	free(cmd->full_path);
	cmd->full_path = NULL;
	return (EXECUTED);
}

int	extern_is_cmd_valid(t_execute *cmd, char **envp)
{
	int		return_value;
	int		index;
	char	**paths;

	return_value = 0;
	index = 0;
	paths = extern_get_path_array(envp);
	if (paths == NULL)
		return (ERROR);
	while (paths[index] != NULL)
	{
		return_value = extern_try_access(cmd, paths[index],
				cmd->order_str);
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

static int	extern_fork_and_execute(t_data *data, int **fd_pipes, int index)
{
	int	pid;

	pid = fork();
	if (pid == ERROR || pid < 0)
	{
		return (ERROR);
	}
	if (pid == 0)
	{
		executor_extern_child_routine(data, fd_pipes, index);
	}
	else
	{
		if (executor_extern_parent_routine(data, fd_pipes) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

int	executor_extern(t_data *data, int **fd_pipes, int index)
{
	int	return_value;

	return_value = extern_is_cmd_valid(data->combine[index].command,
			data->envp);
	if (return_value == 1)
	{
		if (extern_fork_and_execute(data, fd_pipes, index) == ERROR)
		{
			return (ERROR);
		}
		free(data->combine[index].command->full_path);
		data->combine[index].command->full_path = NULL;
	}
	else if (return_value == ERROR)
	{
		return (ERROR);
	}
	else
	{
		printf("WIP: command not found!\n");
		free(data->combine[index].command->full_path);
		data->combine[index].command->full_path = NULL;
	}
	return (EXECUTED);
}

// @todo Error handling!
