/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:50:57 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 21:21:14 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data
#include <stdio.h>		// needed for printf(), perror()
#include "libft.h"		// needed for ft_split()
#include "libme.h"		// needed for free_char_array()
#include <unistd.h>		// needed for chdir(), access(), getcwd()

// argument parsing cd bla bla
// no such file or directory
// update oldpwd
// update pwd
// home
// some_path	| by name directory
// -			| previous directory
// ..			| parent directory
// .			| current directory
// ~			| home directory
// /			| root directory i think

static int	get_envp_var(char **envp, char *var_name, int var_name_length)
{
	int	index;
	
	index = 0;
	while (envp != NULL && envp[index] != NULL)
	{
		if (ft_strncmp(var_name, envp[index], var_name_length) == 0)
		{
			if (*(envp[index + var_name_length]) != '\0')
			{
				return (index);
			}
		}
		index += 1;
	}
	return (-1);
}

static char	*where_is_oldpwd(char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp("OLDPWD=", *envp, 7) == 0)
		{
			if (*(*envp + 7) != '\0')
			{
				return (*envp + 7);
			}
		}
		envp += 1;
	}
	return (NULL);
}

static char	*where_is_home(char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp("HOME=", *envp, 5) == 0)
		{
			//printf("Home var: [%s]\n", *envp + 5);
			if (*(*envp + 5) != '\0')
			{
				return (*envp + 5);
			}
		}
		envp += 1;
	}
	return (NULL);
}

static int	update_envp(t_data *data)
{
	char	*oldpwd;

	// get indexes instead
	oldpwd = data->envp[get_envp_var(data->envp, "OLDPWD", 6)];
	printf("before %s\n", oldpwd);
	free(oldpwd);
	data->envp[get_envp_var(data->envp, "OLDPWD", 6)] = getcwd(NULL, 0);
	printf("%s\n", data->envp[get_envp_var(data->envp, "OLDPWD", 6)]);
	oldpwd = data->envp[get_envp_var(data->envp, "OLDPWD", 6)];
	printf("after %s\n", oldpwd);
	// use getcwd()
	return (EXECUTED);
}

void	builtin_cd(t_data *data, int index)
{
	char	**input;
	
	input = ft_split(data->combine[index].combined_str, ' ');
	if (input == NULL)
	{
		return ; // @note error handling?
	}

	char *temp;
	
	temp = NULL;
	if (input[1] == NULL)
	{
		//printf("youre drunk, go home!\n");
		temp = where_is_home(data->envp);
	}
	else if (ft_strncmp("-", input[1], 1) == 0)
	{
		temp = where_is_oldpwd(data->envp);
		if (temp == NULL)
		{
			// error when oldpwd is not set
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
	}
	else
	{
		temp = input[1];
	}
	//printf("%s\n", temp);
	// test for existence?
	if (temp != NULL)
	{
		if (access(temp, F_OK) == -1)
		{
			perror("access");
			// no such file or directory
		}
		if (chdir(temp) == 1)
		{
			perror("chdir");
		}
	}
	update_envp(data);
	free_char_array(input);
}

//printf("received string: [%s]\n", data->combine[index].combined_str);





