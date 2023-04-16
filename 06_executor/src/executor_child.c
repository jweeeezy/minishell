/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:00:29 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/16 12:59:03 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// needed for child_prepare_pipes()
#include "libft.h"		// needed for ft_split()
#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for execve(), NULL
#include <stdio.h>		// needed for close(), dup2()

static int	child_execute_builtin(t_data *data, int index)
{
	int	cmd_type;

	cmd_type = data->combine[index].command->order_numb;
	if (cmd_type == ECHO)
		echo(data->combine[index], 0, 0, 0);
	else if (cmd_type == REJECTED_ECHO)
		wierd_echo(data->combine[index], 0, 0, 0);
	else if (cmd_type == ENV)
		env(data);
	else if (cmd_type == CD)
		printf("cd executed\n");
	else if (cmd_type == PWD)
		builtin_pwd();
	else if (cmd_type == EXPORT)
		printf("export executed\n");
	else if (cmd_type == UNSET)
		printf("unset executed\n");
	else if (cmd_type == EXIT)
		builtin_exit(data, 0, index);
	else
		return (ERROR);
	return (EXECUTED);
}

static int	child_execute_extern(t_data *data, int index)
{
	char	**cmd_array;

	cmd_array = ft_split(data->combine[index].combined_str, ' ');
	if (cmd_array == NULL)
	{
		exit(ERROR);
	}
	execve(data->combine[index].full_path, cmd_array, data->envp);
	free_char_array(cmd_array);
	perror("execve");
	return (ERROR);
}

void	executor_child(t_data *data, int **fd_pipes, int index,
			int flag_cmd)
{
	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		child_prepare_pipes(data, fd_pipes, data->index_processes,
			data->counter_pipes);
	}
	else
	{
		child_handle_indirection(data);
		child_handle_outdirection(data);
	}
	if (flag_cmd == BUILTIN)
	{
		if (child_execute_builtin(data, index) == ERROR)
		{
			exit(ERROR);
		}
	}
	else if (flag_cmd == EXTERN)
	{
		if (child_execute_extern(data, index) == ERROR)
		{
			exit(ERROR);
		}
	}
	exit(EXECUTED);
}
