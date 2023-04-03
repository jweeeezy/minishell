/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:09:04 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/03 20:42:29 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_private.h"	// needed for executor_child(),
								// executor_parent()
#include "minishell.h"			// needed for t_data
#include <unistd.h>				// needed for NULL, access()
#include "libft.h"				// needed for ft_split(), ft_strlen()
#include "libme.h"				// needed for ft_str_check_needle(),
								// ft_str_join_delimiter()

#include <stdio.h>				// needed for printf()

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

static int	selector_try_access(t_execute *cmd, char *path, char *command)
{
	cmd->full_path = ft_str_join_delimiter(path, "/", command);
	if (cmd->full_path == NULL)
		return (ERROR);
	if (access(cmd->full_path, X_OK) == 0)
		return (EXTERN);
	free(cmd->full_path);
	cmd->full_path = NULL;
	return (COMMAND_NOT_FOUND);
}

static int	selector_is_cmd_valid(t_execute *cmd, char **envp)
{
	int		return_value;
	int		index;
	char	**paths;

	return_value = 0;
	index = 0;
	paths = selector_get_path_array(envp);
	if (paths == NULL)
		return (ERROR);
	while (paths[index] != NULL)
	{
		return_value = selector_try_access(cmd, paths[index],
				cmd->order_str);
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

static int	selector_fork_and_execute(t_data *data, int **fd_pipes, int index,
				int flag_cmd)
{
	if (flag_cmd == ERROR)
	{
		return (ERROR);
	}
	else if (flag_cmd == COMMAND_NOT_FOUND)
	{
		printf("WIP: command not found!\n");
		return (EXECUTED);
	}
	data->child_pids[data->index_processes] = fork();
	if (data->child_pids[data->index_processes] == -1)
	{
		return (ERROR);
	}
	if (data->child_pids[data->index_processes] == 0)
	{
		executor_child(data, fd_pipes, index, flag_cmd);
	}
	else
	{
		executor_parent(data, fd_pipes, index);
	}
	return (EXECUTED);
}

int	executor_cmd_selector(t_data *data, int **fd_pipes, int index)
{
	if (is_builtin(data->combine[index].command->order_numb) == 1)
	{
		if (selector_fork_and_execute(data, fd_pipes, index, BUILTIN) == ERROR)
		{
			return (ERROR);
		}
		return (EXECUTED);
	}
	else if (selector_fork_and_execute(data, fd_pipes, index,
			selector_is_cmd_valid(data->combine[index].command,
				data->envp)) == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}
