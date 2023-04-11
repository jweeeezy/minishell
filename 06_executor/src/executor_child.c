/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:00:29 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/11 16:22:47 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_private.h"	// needed for child_prepare_pipes()
#include "libft.h"				// needed for ft_split()
#include "minishell.h"			// needed for t_data, debug()
#include <unistd.h>				// needed for execve(), NULL
#include <stdio.h>				// needed for close(), dup2()

static int	child_execute_builtin(t_data *data, int index)
{
	int	cmd_type;

	cmd_type = data->combine[index].command->order_numb;
	if (cmd_type == ECHO)
		echo(data->combine[index]);
	else if (cmd_type == ECHO_N)
		echo_n(data, index);
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
		printf("exit executed\n");
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
	if (DEBUG)
	{
		printf("t_combine: full_path: [%s]\n\n",
			data->combine[index].full_path);
		printf("Output:\n");
	}
	execve(data->combine[index].full_path, cmd_array, data->envp);
	free_char_array(cmd_array);
	perror("execve");
	return (ERROR);
}

void	executor_child(t_data *data, int **fd_pipes, int index,
			int flag_cmd)
{
	debug_print_pid("Child process");
	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		child_prepare_pipes(fd_pipes, data->index_processes,
			data->counter_pipes);
	}
	else
	{
		printf("yup\n");
		printf("%d\n", data->fd_infile);
		redirector_handler_input(data);
		redirector_handler_output(data);
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
