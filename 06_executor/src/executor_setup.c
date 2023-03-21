/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:57:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/21 11:17:09 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libme.h"
#include "libft.h"
#include <unistd.h>
#include "executor_private.h"

int	try_access(t_combine *cmd, char *path, char *command)
{	
	cmd->full_path = ft_str_join_delimiter(path, "/", command);
	if (cmd->full_path == NULL)
	{
		return (ERROR);
	}
	if (access(cmd->full_path, X_OK) == 0)
	{
		return (1);
	}
	free(cmd->full_path);
	cmd->full_path = NULL;
	return (EXECUTED);
}

int	check_valid_command(t_combine *cmd, char **envp)
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
		return_value = try_access(cmd->command, paths[index], cmd->command->order_str );
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

char	**convert_str_to_array(t_combine *cmd)
{
	char	**array_command;

	array_command = ft_split(cmd->combined_str, ' ');
	return (array_command);
}