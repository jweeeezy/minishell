/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:28:59 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/25 21:21:18 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data
#include "libft.h"		// needed for ft_split(), ft_strlen(), ft_strncmp()
#include "libme.h"		// needed for free_char_array()
#include <stdio.h>		// needed for printf(), perror()
#include <unistd.h>		// needed for chdir(), access(), getcwd()

static char	*get_var_content(char **envp, char *var_name)
{
	int	var_name_length;

	var_name_length = ft_strlen(var_name);
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(var_name, *envp, var_name_length) == 0)
		{
			if (*(*envp + var_name_length) != '\0')
			{
				return (*envp + var_name_length);
			}
		}
		envp += 1;
	}
	return (NULL);
}

static int	find_var_index(char **envp, char *var_name)
{
	int	index;
	int	var_name_length;

	var_name_length = ft_strlen(var_name);
	index = 0;
	while (envp != NULL && envp[index] != NULL)
	{
		if (ft_strncmp(var_name, envp[index], var_name_length) == 0)
		{
			return (index);
		}
		index += 1;
	}
	return (0);
}

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

static char	*handle_tilde_with_arguments(t_data *data, int index, char **input,
		char *temp)
{
	char	*another_temp;

	another_temp = ft_substr(input[1], 1, ft_strlen(input[1]) - 1);
	if (another_temp == NULL)
	{
		return (NULL);
	}
	temp = ft_strjoin(temp, another_temp);
	free(another_temp);
	return (temp);
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

static int	get_path(char **input)
{
	char	*temp;

	temp = NULL;
	if (input[1] == NULL || ft_strncmp("~", input[1], 1) == 0)
	{
		temp = get_var_content(data->envp, "HOME=");
		if (temp == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
		}
		if (temp != NULL && ft_strlen(input[1]) > 1)
		{
			temp = handle_tilde_with_arguments(data, index, input, temp);
		}
	}
	else if (ft_strncmp("-", input[1], 1) == 0)
	{
		temp = get_var_content(data->envp, "OLDPWD=");
		if (temp == NULL)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
	}
	else
	{
		temp = input[1];
	}
	return (temp);
}

int	builtin_cd(t_data *data, int index)
{
	char	**input;

	input = ft_split(data->combine[index].combined_str, ' ');
	if (input == NULL)
	{
		return (ERROR);
	}
	temp = get_path(input);
	if (temp == NULL)
	{
		free_char_array(input);
		data->exit_status = 1;
		return (ERROR);
	}
	if (change_directory(temp) == ERROR)
	{
		free_char_array(input);
		data->exit_status = 1;
		return (ERROR);
	}
	if (update_envp(data) == ERROR)
	{
		free_char_array(input);
		data->exit_status = 1;
		return (ERROR);
	}
	free_char_array(input);
	return (EXECUTED);
}
