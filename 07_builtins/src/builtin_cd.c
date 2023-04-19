/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:50:57 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/18 21:08:24 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data
#include <stdio.h>		// needed for printf()
#include "libft.h"		// needed for ft_split()
#include "libme.h"		// needed for free_char_array();

// argument parsing cd bla bla
// no such file or directory
// oldpwd
// pwd
// home
// some_path	| by name directory
// -			| previous directory
// ..			| parent directory
// .			| current directory
// ~			| home directory
// /			| root directory i think


static char	*where_is_home(char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp("HOME=", *envp, 5));
		{
			printf("Home var: [%s]\n", *envp);
			return (*envp);
		}
		envp += 1;
	}
	return (NULL);
}

void	builtin_cd(t_data *data, int index)
{
	char	**input;

	input = ft_split(data->combine[index].combined_str, ' ');
	if (input == NULL)
	{
		return ; // @note error handling?
	}
	if (input[1] == NULL)
	{
		// go home
		printf("youre drunk, go home!\n");
		where_is_home(data->envp);
	}
	else
	{
		printf("do cd\n");
	}
	free_char_array(input);
}

//printf("received string: [%s]\n", data->combine[index].combined_str);

