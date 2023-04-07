/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/07 17:33:35 by jwillert         ###   ########          */
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

int	heredoc_create_pipe(t_heredoc *node_to_edit)
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
		delimiter = NULL;
	}
	return (delimiter);
}

t_heredoc	*heredoc_create_lst(t_data *data)
{
	t_heredoc	*node_to_edit;

	if (data->heredoc == NULL)
	{
		data->heredoc = heredoc_get_new_node();
		node_to_edit = data->heredoc;
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

int	heredoc_open_heredoc(t_data *data, int index, t_heredoc *current_node)
{
	char		*heredoc_line;
	char		*heredoc_delimiter;

	if (current_node == NULL)
	{
		heredoc_clean_lst(data, -1);
		return (ERROR);
	}
	heredoc_delimiter = heredoc_get_delimiter(data, index);
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

		ft_putstr_fd(heredoc_line, current_node->fd_pipe[1]);
		close (current_node->fd_pipe[0]);
		free(heredoc_line);
	}
	free(heredoc_line);
	return (EXECUTED);
}

t_heredoc	*redirector_heredoc_update_lst(t_data *data)
{
	t_heredoc *current_node;

	if (data->heredoc == NULL)
	{
		current_node = heredoc_create_lst(data);
	}
	else
	{
		current_node = heredoc_add_back(data->heredoc, heredoc_create_lst(data));
	}
	return (current_node);
}

int	redirector_prehandle_heredocs(t_data *data, int counter_heredocs)
{
	int				index;
	int				id;
	t_heredoc		*current_node;
	//t_vector_str	*buffer;

	index = 0;
	while (index < counter_heredocs)
	{
		if (data->combine[index].command->order_numb == HERE_DOC)
		{
			current_node = redirector_heredoc_update_lst(data);
			id = fork();
			if (id == 0)
			{
				heredoc_child_close_fd_before(data, current_node);
				if (heredoc_open_heredoc(data, index, current_node) == ERROR)
				{
					exit(ERROR);
				}
				exit(EXECUTED);
			}
			else
			{
				wait(NULL);
				//buffer = ft_vector_str_join(buffer, 
						//get_next_line(current_node->fd_pipe[0]), 0);
				//printf("%s\n", buffer->str);
			}
		}
		index += 1;
	}
	return (EXECUTED);
}

