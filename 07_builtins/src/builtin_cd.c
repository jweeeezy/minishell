/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:28:59 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/26 16:13:49 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"		// needed for ft_strjoin()
#include "libme.h"		// needed for free_char_array()
#include "minishell.h"	// needed for t_data, MACROS
#include <unistd.h>		// needed for access(), free(), chdir(), getcwd()
#include <stdio.h>		// needed for perror()
#include "builtins.h"	// needed for find_var_index()

static int	update_envp(t_data *data)
{
	int	index_oldpwd;
	int	index_pwd;

	index_oldpwd = find_var_index(data->envp, "OLDPWD=");
	index_pwd = find_var_index(data->envp, "PWD=");
	free(data->envp[index_oldpwd]);
	data->envp[index_oldpwd] = ft_strjoin("OLD", data->envp[index_pwd]);
	if (data->envp[index_oldpwd] == NULL)
	{
		return (ERROR);
	}
	free(data->envp[index_pwd]);
	data->envp[index_pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (data->envp[index_pwd] == NULL)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

static int	change_directory(char *path)
{
	if (access(path, F_OK) == -1)
	{
		perror("access");
		return (ERROR);
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (ERROR);
	}
	return (EXECUTED);
}

static int	change_directory_and_update_envp(t_data *data, char *temp)
{
	if (change_directory(temp) == ERROR)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	if (update_envp(data) == ERROR)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	return (EXECUTED);
}

int	builtin_cd(t_data *data, int index)
{
	char	**input;
	char	*temp;

	input = ft_split(data->combine[index].combined_str, ' ');
	if (input == NULL)
	{
		return (ERROR);
	}
	temp = get_destination(data, input, NULL);
	if (temp == NULL)
	{
		free_char_array(input);
		data->exit_status = 1;
		return (ERROR);
	}
	if (change_directory_and_update_envp(data, temp) == ERROR)
	{
		free_char_array(input);
		return (ERROR);
	}
	free_char_array(input);
	return (EXECUTED);
}
