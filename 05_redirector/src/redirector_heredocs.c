/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/12 17:07:07 by jwillert         ###   ########.fr       */
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

static char	*heredoc_get_delimiter(t_data *data, int index)
{
	char	*delimiter;

	delimiter = data->combine[index].combined_str + 2;
	if (*delimiter == '\0')
	{
		delimiter = NULL;
	}
	return (delimiter);
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

	current_node = heredoc_lst_update(data);
	if (current_node == NULL)
	{
		return (ERROR);
	}
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

int	redirector_prehandle_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;

	index = 0;
	counter_heredocs = executor_count_heredocs(data);
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
