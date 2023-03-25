/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:02:06 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/25 21:09:30 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_private.h"

int	executor_select_cmd(t_data *data, int **fd_pipes, int index)
{
	if (is_builtin(data->combine[index]) == 1)
	{
		if (executor_builtin(data, fd_pipes, index) == ERROR)
		{
			return (ERROR);
		}
	}
	else
	{
		if (executor_extern(data, fd_pipes, index) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

int	executor_main(t_data *data)
{
	data->counter_pipes = count_pipes(data);
	data->index_processes = 0;
	if (data->counter_pipes != 0)
	{
		if (executor_pipex(data) == ERROR)
		{
			return (ERROR);
		}
	}
	else
	{
		if (executor_select_cmd(data, NULL, 0) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

//	@todo Handle HEREDOC
//	@todo Handle REDIRECTION
