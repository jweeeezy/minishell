/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/02 10:36:50 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"

int	executor_main(t_data *data)
{
	int		id;
	char	*path
	char	*command;

	command = data->execute->order_str;
	// if its valid path
		path = command;
	// if its not valid path
		path = ft_strjoin("/bin/", command)
	id = fork()
	if (id == =1)
	{
		return (-1);
	}
	if (id == 0)
	{
		return (execve(path, data->args, data->envp));
	}
	else
	{
		if (wait(NULL) == -1)
			return (-1);
	}
	return(0);
}
