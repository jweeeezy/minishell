/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/04 19:41:24 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"		// needed for t_data
#include "libft.h"			// needed for ft_strncmp(), ft_strlen()
#include <fcntl.h>			// needed for open()
#include <time.h>			// needed for time()

int	heredoc_create_pipe(t_heredoc *note_to_edit)
{
	int	*fd_pipe;

	fd_pipe = malloc (sizeof (int) * 2);
	if (fd_pipe == NULL)
	{
		return (ERROR);
	}
	if (pipe(fd_pipe) == -1)
	{
		free(fd_pipe);
		return (ERROR);
	}
	node_to_edit->fd_pipe = fd_pipe;
	return (EXECUTED);
}

char	*heredoc_get_delimiter(t_data *data, int index)
{
	char	*delimiter;

	delimiter = data->combine[index].combined_str + 2;
	if (*delimiter == '\0')
	{
		delimiter == NULL;
	}
	return (delimiter);
}

t_heredoc	*heredoc_create_heredoc_lst(t_data *data)
{
	t_heredoc	*node_to_edit;

	if (data->heredoc == NULL)
	{
		data->heredoc = heredoc_get_new_node();
		note_to_edit = data->heredoc;
	}
	else
	{
		node_to_edit = heredoc_add_back(data->heredoc, heredoc_get_new_node());
	}
	if (node_to_edit == NULL)
	{
		return (NULL);
	}
	if (heredoc_create_pipe(node_to_edit) == ERROR)
	{
		free(node_to_edit);
		return (NULL);
	}
	return (node_to_edit);
}

int	heredoc_open_heredoc(t_data *data, int index)
{
	char		*heredoc_line;
	char		*heredoc_delimiter;
	t_heredoc	*current_node;

	heredoc_delimiter = heredoc_get_delimiter(data, index);
	current_node = heredoc_create_heredoc(data);
	if (current_node == NULL)
	{
		heredoc_clean_list(data, -1);
		return (ERROR);
	}
	while (1)
	{
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
				break ;
			}
		}
		// write to tmp file should be done in child
		// or parent writes to the pipe, child reads from it?
		free(heredoc_line);
	}
	free(heredoc_line);
	return (EXECUTED);
}

int	redirector_open_heredocs(t_data *data, int counter_heredocs)
{
	int	index;
	int	id;

	index = 0;
	while (index < counter_heredocs)
	{
		if (data->combine[index].command->order_numb == HEREDOC)
		{
			id = fork();
			if (id == 0)
			{
				if (heredoc_open_heredoc(data, index) == ERROR)
				{
					exit(ERROR);
				}
				exit(EXECUTED);
			}
			else
			{
				wait(NULL);
			}
		}
		index += 1;
	}
	return (EXECUTED);
}

// @note can prob rewrite so I dont to go trough all heredocs first?
