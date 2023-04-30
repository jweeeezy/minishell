/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:00:29 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 15:57:44 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// needed for child_prepare_pipes()
#include "libft.h"		// needed for ft_split()
#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for execve(), NULL
#include <stdio.h>		// needed for close(), dup2()

void	handle_heredoc(t_data *data);

int	child_execute_builtin(t_data *data, int index)
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
		builtin_cd(data, index);
	else if (cmd_type == PWD)
		builtin_pwd();
	else if (cmd_type == EXPORT)
		builtin_export(data, index);
	else if (cmd_type == UNSET)
		unset(data, index);
	else if (cmd_type == EXIT)
		builtin_exit(data, 0, index);
	else
		return (ERROR);
	return (EXECUTED);
}

static int	child_count_non_white_tokens(t_data *data, int index)
{
	int	index_tokens;
	int	counter_non_white;

	index_tokens = 0;
	counter_non_white = 0;
	while (index_tokens < data->combine[index].count_n)
	{
		if (data->combine[index].execute[index_tokens].order_numb != WHITE)
		{
			counter_non_white += 1;
		}
		index_tokens += 1;
	}
	return (counter_non_white);
}

static char	**child_copy_tokens(t_data *data, int index)
{
	int		array_index;
	int		execute_index;
	int		counter_non_white;
	char	**cmd_array;

	execute_index = 0;
	array_index = 0;
	counter_non_white = child_count_non_white_tokens(data, index);
	cmd_array = malloc(sizeof (char *) * (counter_non_white + 1));
	if (cmd_array == NULL)
	{
		return (NULL);
	}
	while (execute_index < data->combine[index].count_n)
	{
		if (data->combine[index].execute[execute_index].order_numb != WHITE)
		{
			cmd_array[array_index]
				= data->combine[index].execute[execute_index].order_str;
			array_index += 1;
		}
		execute_index += 1;
	}
	cmd_array[array_index] = NULL;
	return (cmd_array);
}

static int	child_execute_extern(t_data *data, int index)
{
	char	**cmd_array;

	cmd_array = child_copy_tokens(data, index);
	if (cmd_array == NULL)
	{
		return(ERROR);
	}
	if (data->exit_status == 0)
	{
		execve(data->combine[index].full_path, cmd_array, data->envp);
		if (data->flag_printed == 0)
		{
			perror("execve");
			data->flag_printed = 1;
		}
		return (EXECUTED);
	}
	free_char_array(cmd_array);
	return (EXECUTED);
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
		child_handle_outdirection(data);
		child_handle_indirection(data);
	}
	if (flag_cmd == NO_EXECUTION)
	{
		if (data->flag_infile == 1 || data->flag_outfile == 1 || data->flag_heredoc == 1)
		{
			data->exit_status = 0;
		}
		else
		{
			data->exit_status = 1;
		}
	}
	else if (flag_cmd == BUILTIN)
	{
		if (child_execute_builtin(data, index) == ERROR)
		{
			data->exit_status = ERROR;
		}
	}
	else if (flag_cmd == EXTERN)
	{
		if (child_execute_extern(data, index) == ERROR)
		{
			data->exit_status = ERROR;
		}
	}
	else if (flag_cmd == COMMAND_NOT_FOUND && data->exit_status == 0)
	{
		data->exit_status = 127;
	}
	free_pipe_array(fd_pipes, data->counter_pipes);
	if (data->heredoc != NULL)
	{
		free_t_heredoc(data);
	}
	if (data->combine[index].full_path != NULL)
	{
		free(data->combine[index].full_path);
	}
	free(data->child_pids);
	free_env(data);
	free_loop(data);
	exit(data->exit_status);
}
