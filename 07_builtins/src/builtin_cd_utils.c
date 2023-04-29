/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:25:39 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/29 14:54:10 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"		// needed for ft_strlen(), ft_strncmp(), ft_substr(),
						// ft_strjoin(), ft_putstr_fd()
#include "minishell.h"	// needed for t_data, MACROS
#include <unistd.h>		// needed for NULL, free()

char	*get_var_content(char **envp, char *var_name)
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

int	find_var_index(char **envp, char *var_name)
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

static char	*handle_tilde_with_arguments(char **input, char *temp, 
		int *flag_allocation)
{
	char	*another_temp;

	another_temp = ft_substr(input[1], 1, ft_strlen(input[1]) - 1);
	if (another_temp == NULL)
	{
		return (NULL);
	}
	temp = ft_strjoin(temp, another_temp);
	*flag_allocation = 1;
	free(another_temp);
	return (temp);
}

char	*get_destination(t_data *data, char **input, char *temp,
			int *flag_allocation)
{
	if (input[1] == NULL || ft_strncmp("~", input[1], 1) == 0)
	{
		temp = get_var_content(data->envp, "HOME=");
		if (temp == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
		}
		if (temp != NULL && ft_strlen(input[1]) > 1)
		{
			temp = handle_tilde_with_arguments(input, temp, flag_allocation);
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
		temp = input[1];
	return (temp);
}
