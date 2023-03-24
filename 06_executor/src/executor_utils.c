/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:20:28 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/23 09:45:35 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, t_execute
#include "libft.h"		// needed for ft_split(), ft_strlen()

int	count_pipes(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	cnt1 = 0;
	while (cnt < data->commands_to_process)
	{
		if (data->combine[cnt].command->order_numb == PIPE
		|| data->combine[cnt].command->order_numb == LAST_PIPE)
			cnt1++;
		cnt++;
	}
	return (cnt1);
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
		&& offset[index].order_numb != LAST_PIPE)
	{
		index += 1;
	}
	return (&offset[index]);
}
