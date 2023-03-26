/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_extern_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:00:29 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/26 16:51:16 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"		// needed for ft_split()
#include "minishell.h"	// needed for t_data, debug()
#include <unistd.h>		// needed for execve(), NULL
#include <stdio.h>		// needed for close(), dup2()

static void	child_close_pipes_before(int **fd_pipes, int end)
{
	int	index;

	index = 0;
	while (index < end && fd_pipes[index] != NULL)
	{
		if (index != end - 1)
			close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index += 1;
	}
}

static void	child_close_pipes_after(int **fd_pipes, int start)
{
	int	index;

	index = start;
	while (fd_pipes[index] != NULL)
	{
		close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index += 1;
	}
}

static void	child_prepare_pipes(int **fd_pipes, int index, int counter_pipes)
{
	if (index == 0)
	{
		close(fd_pipes[0][0]);
		child_close_pipes_after(fd_pipes, index + 1);
		debug_print_pipe_status("__in Child ---first---", fd_pipes);
		dup2(fd_pipes[0][1], STDOUT_FILENO);
	}
	else if (index == counter_pipes)
	{
		close(fd_pipes[index - 1][1]);
		debug_print_pipe_status("__in Child ***LAST***", fd_pipes);
		dup2(fd_pipes[index - 1][0], STDIN_FILENO);
	}
	else
	{
		close(fd_pipes[index][0]);
		child_close_pipes_before(fd_pipes, index);
		child_close_pipes_after(fd_pipes, index + 1);
		debug_print_pipe_status("__in Child :::Middle:::", fd_pipes);
		dup2(fd_pipes[index][1], STDOUT_FILENO);
		dup2(fd_pipes[index - 1][0], STDIN_FILENO);
	}
}

void	executor_extern_child_routine(t_data *data, int **fd_pipes, int index)
{
	char	**cmd_array;

	if (fd_pipes != NULL && data->counter_pipes != 0)
	{
		child_prepare_pipes(fd_pipes, data->index_processes,
			data->counter_pipes);
	}
	cmd_array = ft_split(data->combine[index].combined_str, ' ');
	if (cmd_array == NULL)
	{
		exit(ERROR);
	}
	execve(data->combine[index].command->full_path, cmd_array, data->envp);
	free_char_array(cmd_array);
	perror("execve");
	exit(ERROR);
}
