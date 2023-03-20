/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:20:28 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/20 18:16:06 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, t_execute
#include "libft.h"		// needed for ft_split(), ft_strlen()

int	count_pipes(t_execute *execute)
{
	int	index_str;
	int	index_array;
	int	counter;

	index_str = 0;
	index_array = 0;
	counter = 0;
	while (execute[index_array].order_str != NULL)
	{
		while (execute[index_array].order_str[index_str] != '\0')
		{
			if (execute[index_array].order_str[index_str] == '|')
			{
				counter += 1;
			}
			index_str += 1;
		}
		index_str = 0;
		index_array += 1;
	}
	return (counter);
}

char	**get_path_array(char **envp)
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

t_execute	*get_pipe(t_execute *offset)
{
	int	index;

	index = 0;
	while (offset[index].order_str != NULL
		&& offset[index].order_numb != PIPE
		&& offset[index].order_numb != PIPE_LAST)
	{
		index += 1;
	}
	return (&offset[index]);
}

t_execute	*get_string_after_pipe(t_execute *offset, t_execute *next_pipe)
{
	int	index;

	index = 0;
	while (&offset[index] != next_pipe
		&& offset[index].order_str != NULL)
	{
		index += 1;
	}
	while (offset[index].order_numb != STRING
		&& offset[index].order_str != NULL)
	{
		index += 1;
	}
	return (&offset[index]);
}

t_execute	*get_string_after_whitespaces(t_execute *execute)
{
	int	index;

	index = 0;
	if (execute == NULL)
	{
		return (NULL);
	}
	while (execute[index].order_numb == 1 || execute[index].order_numb == 2)
	{
		index += 1;
	}
	return (&execute[index]);
}
