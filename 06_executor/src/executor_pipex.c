/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:47:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/24 18:23:05 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_private.h"
#include <stdio.h>
#include <unistd.h>

static void close_pipes_before(int **fd_pipes, int i)
{
	int	index;

	index = 0;
	while (index < i && fd_pipes[index] != NULL)
	{
		if (index != i - 1)
			close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index++;
	}
}

static void	close_pipes_after(int **fd_pipes, int i, int counter_pipes)
{
	while(fd_pipes[i] != NULL && i < counter_pipes)
	{
		close(fd_pipes[i][0]);
		close(fd_pipes[i][1]);
		i++;
	}
}

static void	close_unused_pipes_child(int **fd_pipes, int index,
		int counter_pipes)
{
	if (index == 0)						// FIRST PIPE
	{
		close(fd_pipes[0][0]);
		dup2(fd_pipes[0][1], STDOUT_FILENO);
		close_pipes_after(fd_pipes, 1, counter_pipes);
	}
	else if (index != counter_pipes - 1)	//	LAST PIPE
	{
		close(fd_pipes[index][1]);
		dup2(fd_pipes[index][0], STDIN_FILENO);
		close_pipes_before(fd_pipes, index);
	}
	else								//	MIDDLE PIPES
	{
		close(fd_pipes[index][0]);
		dup2(fd_pipes[index][1], STDOUT_FILENO);
		dup2(fd_pipes[index - 1][0], STDIN_FILENO);
		close_pipes_before(fd_pipes, index);
		close_pipes_after(fd_pipes, index + 1, counter_pipes);
	}
}

static void	close_unused_pipes_parent(int **fd_pipes, int counter_pipes)
{
	int index;

	index = 0;
	while (fd_pipes[index] != NULL && index < counter_pipes)
	{
		close(fd_pipes[index][0]);
		close(fd_pipes[index][1]);
		index++;
	}
}

static void child_routine(t_data *data, int index)
{
	char	**cmd_array;
  
	cmd_array = convert_str_to_array(&data->combine[index]);
	if (cmd_array == NULL)
	{
		exit(ERROR);
	}
	if (execve(data->combine[index].command->full_path,
			   	cmd_array, data->envp) == -1)
	{
		free_char_array(cmd_array);
		perror("execve");
		printf("child here\n");
		exit(ERROR);
	}
}

static int execute_fork_and_execute(t_data *data, int index, int **fd_pipes,
		int counter_pipes)
{
	int 	pid;

	pid = fork();
	if (pid == ERROR || pid < 0)
	{
		printf("here\n");
		return (ERROR);
	}
	if (pid == 0)
	{
		if (fd_pipes != NULL && counter_pipes != 0)
		{
			close_unused_pipes_child(fd_pipes, data->index_processes,
				   	counter_pipes);
		}
		child_routine(data, index);
	}
	else
	{
		if (wait(NULL) == -1)
		{
			printf("or here?\n");
			perror("wait");
			return (ERROR);
		}
	}
	return(EXECUTED);
}

static int	**create_pipes(int counter_pipes)
{
	int	**fd_pipes;
	int	index;

	index = 0;
	fd_pipes = malloc (sizeof (int *) * (counter_pipes + 1));
	if (fd_pipes == NULL)
	{
		return (NULL);
	}
	while (index < counter_pipes)
	{
		fd_pipes[index] = malloc (sizeof (int) * 2);
		if (fd_pipes[index] == NULL)
		{
			free_int_array(fd_pipes, index);
			return (NULL);
		}
		index += 1;
	}
	fd_pipes[counter_pipes] = NULL;
	return (fd_pipes);
}

int	executor_pipex(t_data *data, int counter_pipes)
{
	int	**fd_pipes;
	int	index;
	int	return_value;

	index = 0;
	fd_pipes = create_pipes(counter_pipes);
	if (fd_pipes == NULL)
	{
		return (ERROR);
	}
	close_unused_pipes_parent(fd_pipes, counter_pipes);
	while (index < counter_pipes + counter_pipes + 1)
	{
		if (data->combine[index].command->order_numb == PIPE
			|| data->combine[index].command->order_numb == LAST_PIPE)
		{
			index += 1;
		}
		return_value = check_valid_command(data->combine[index].command,
			  data->envp);
		if (return_value == 1)
		{
			if (execute_fork_and_execute(data, index,
					   	fd_pipes, counter_pipes) == ERROR)
			{
				return (ERROR);
			}
			free(data->combine[index].command->full_path);
			data->combine[index].command->full_path = NULL;
			index += 1;
			data->index_processes += 1;
		}
		else if (return_value == ERROR)
		{
			return (ERROR);
		}
	}
	//free_int_array(fd_pipes, counter_pipes);
	return (EXECUTED);
}

int	executor_execute(t_data *data)
{
	int	return_value;

	return_value = check_valid_command(data->combine->command, data->envp);
	if (return_value == 1)
	{
		if (execute_fork_and_execute(data, 0, NULL, 0) == ERROR)
		{
			return (ERROR);
		}
	}
	else if (return_value == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

void	executor_decide(t_data *data)
{
	data->counter_pipes = count_pipes(data);
	data->index_processes = 0;
	if (data->counter_pipes != 0)
	{
		executor_pipex(data, data->counter_pipes);
	}
	else
	{
		executor_execute(data);
	}
}
