/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/12 16:26:40 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector_private.h"
#include "minishell.h"		// needed for t_data
#include "libft.h"			// needed for ft_strncmp(), ft_strlen()
#include <fcntl.h>			// needed for open()
#include <time.h>			// needed for time()
#include <unistd.h>			// needed for pipe(), open(), close()
#include <readline/readline.h>
#include <readline/history.h>

static int	heredoc_create_file(t_heredoc *node_to_edit)
{
	if (heredoc_get_full_path(node_to_edit) == ERROR)
	{
		return (ERROR);
	}
	if (node_to_edit->full_path == NULL)
	{
		return (ERROR);
	}
	node_to_edit->fd = open(node_to_edit->full_path,
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (node_to_edit->fd < 0)
	{
		free(node_to_edit->full_path);
		return (ERROR);
	}
	return (EXECUTED);
}

static int	heredoc_loop(t_heredoc *current_node, char *heredoc_delimiter)
{
	char	*heredoc_line;

	heredoc_line = readline(">");
	if (heredoc_line == NULL)
	{
		return (ERROR);
	}
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

static int	heredoc_open_heredoc(t_data *data, int index,
			t_heredoc *current_node)
{
	int		return_value;
	char	*heredoc_delimiter;

	return_value = 0;
	if (current_node == NULL)
	{
		heredoc_lst_clean(data, -1);
		return (ERROR);
	}
	heredoc_delimiter = heredoc_get_delimiter(data, index);
	while (1)
	{
		return_value = heredoc_loop(current_node, heredoc_delimiter);
		if (return_value != EXECUTED)
		{
			break ;
		}
	}
	return (return_value);
}

static int	heredoc_fork_and_open(t_data *data, int index,
		int counter_heredocs)
{
	t_heredoc	*current_node;
	int			id;

	current_node = heredoc_lst_get_and_update_lst(data);
	id = fork();
	if (id == 0)
	{
		if (heredoc_open_heredoc(data, index, current_node) == ERROR)
		{
			exit(ERROR);
		}
		close(current_node->fd);
		exit(EXECUTED);
	}
	else
	{
		wait(NULL);
		close(current_node->fd);
	}
	return (EXECUTED);
}

int	redirector_prehandle_heredocs(t_data *data, int counter_heredocs)
{
	int				index;

	index = 0;
	while (data->combine[index].combined_str != NULL && counter_heredocs > 0)
	{
		if (data->combine[index].command->order_numb == HERE_DOC)
		{
			if (heredoc_fork_and_open(data, index, counter_heredocs) == ERROR)
			{
				return (ERROR);
			}
			counter_heredocs -= 1;
		}
		index += 1;
	}
	return (EXECUTED);
}
