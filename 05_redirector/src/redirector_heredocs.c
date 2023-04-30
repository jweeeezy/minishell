/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 17:45:44 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector.h"			// needed for heredoc_*()
#include "executor.h"			// needed for executor_count_heredocs()
#include "minishell.h"			// needed for t_data
#include "libft.h"				// needed for ft_strncmp(), ft_strlen(),
								// ft_putstr_fd()
#include <fcntl.h>				// needed for open()
#include <unistd.h>				// needed for close(), fork()
#include <readline/readline.h>	// needed for readline()
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>
//#include <sys/types.h>

static char	*heredoc_get_delimiter(t_data *data, int index)
{
	char	*offset_ptr;
	char	*delimiter;
	size_t	length;

	offset_ptr = data->combine[index].combined_str + 2;
	length = ft_strlen(offset_ptr);
	delimiter = ft_substr(offset_ptr, 0, length);
	return (delimiter);
}

static int	heredoc_loop(t_data *data, t_heredoc *current_node,
	char *heredoc_delimiter, int mode)
{
	char	*heredoc_line;

	heredoc_line = readline("> ");
	if (heredoc_line == NULL)
		return (ERROR);
	if (mode == QUOTED_HEREDOC)
		heredoc_line = expand_heredocs(data, heredoc_line);
	if (heredoc_delimiter != NULL)
	{
		if (ft_strncmp(heredoc_line, heredoc_delimiter,
				ft_strlen(heredoc_delimiter)) == 0)
		{
			ft_putstr_fd("\0", current_node->fd);
			free(heredoc_line);
			return (1);
		}
	}
	ft_putstr_fd(heredoc_line, current_node->fd);
	ft_putstr_fd("\n", current_node->fd);
	return (EXECUTED);
}

static int	heredoc_open_heredoc(t_data *data, int index, t_heredoc *c_node)
{
	int		return_value;
	char	*heredoc_delimiter;

	return_value = 0;
	if (c_node == NULL)
	{
		heredoc_lst_clean(data);
		return (ERROR);
	}
	heredoc_delimiter = heredoc_get_delimiter(data, index);
	if (heredoc_delimiter == NULL)
	{
		heredoc_lst_clean(data);
		return (ERROR);
	}
	while (1)
	{
		return_value = heredoc_loop(data, c_node, heredoc_delimiter,
				data->combine[index].command->order_numb);
		if (return_value != EXECUTED)
			break ;
	}
	free(heredoc_delimiter);
	return (return_value);
}

static int	heredoc_fork_and_open(t_data *data, int index, int id, int status)
{
	t_heredoc	*current_node;

	current_node = heredoc_lst_update(data);
	if (current_node == NULL)
		return (ERROR);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		heredoc_signals();
		status = heredoc_open_heredoc(data, index, current_node);
		if (status == ERROR)
			exit(ERROR);
		close(current_node->fd);
		exit(EXECUTED);
	}
	else
	{
		wait(&status);
		close(current_node->fd);
	}
	if (status == 512)
		return (-2);
	return (EXECUTED);
}

int	redirector_prehandle_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;
	int	status;

	index = 0;
	debug_print_stage("prehandler heredoc", 0);
	counter_heredocs = executor_count_heredocs(data);
	while (index < data->commands_to_process && counter_heredocs > 0)
	{
		if (data->combine[index].command->order_numb == HERE_DOC
			|| data->combine[index].command->order_numb == QUOTED_HEREDOC)
		{
			status = heredoc_fork_and_open(data, index, 0, 0);
			if (status == ERROR)
				return (ERROR);
			else if (status == -2)
				return (-2);
			counter_heredocs -= 1;
		}
		index += 1;
	}
	debug_print_t_heredoc(data);
	return (EXECUTED);
}
