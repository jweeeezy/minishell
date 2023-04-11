/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/11 20:10:23 by jwillert         ###   ########.fr       */
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

int	heredoc_check_duplicate_hash(t_heredoc *head, t_heredoc *node_to_compare)
{
	while (head != NULL)
	{
		if (head == node_to_compare)
		{
			head = head->next;
		}
		if (node_to_compare->hash == head->hash)
		{
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	heredoc_create_hash(char *string_to_hash)
{
	unsigned long int	hash;
	int					value;

	value = ft_atoi(string_to_hash);
	while (*string_to_hash != '\0')
	{
		hash = ((hash << 5) + hash) + *string_to_hash;
		string_to_hash += 1;
	}
	return (hash * value);
}

int	heredoc_get_full_path(t_heredoc *node_to_edit)
{
	char	*path;
	char	*hash_str;
	char	*temp;

	path = ft_strdup("/tmp/");
	if (path == NULL)
	{
		return (ERROR);
	}
	temp = ft_itoa_unsigned_long((unsigned long int) node_to_edit);
	node_to_edit->hash = heredoc_create_hash(temp);
	free(temp);
	hash_str = ft_itoa_unsigned_long(node_to_edit->hash);
	if (hash_str == NULL)
	{
		free(path);
		return (ERROR);
	}
	node_to_edit->full_path = ft_strjoin(path, hash_str);
	free(path);
	free(hash_str);
	return (EXECUTED);
}

int	heredoc_create_file(t_heredoc *node_to_edit)
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
	if (heredoc_create_file(node_to_edit) == ERROR)
	{
		free(node_to_edit);
		return (NULL);
	}
	return (node_to_edit);
}

int	heredoc_loop(t_heredoc *current_node, char *heredoc_delimiter)
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

int	heredoc_open_heredoc(t_data *data, int index, t_heredoc *current_node)
{
	int		return_value;
	char	*heredoc_delimiter;

	return_value = 0;
	if (current_node == NULL)
	{
		heredoc_clean_lst(data, -1);
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

t_heredoc	*redirector_heredoc_update_lst(t_data *data)
{
	t_heredoc	*current_node;

	if (data->heredoc == NULL)
	{
		current_node = heredoc_create_lst(data);
	}
	else
	{
		current_node = heredoc_add_back(data->heredoc,
				heredoc_create_lst(data));
	}
	return (current_node);
}

int	redirector_fork_and_open_heredoc(t_data *data, int index,
		int counter_heredocs)
{
	t_heredoc	*current_node;
	int			id;

	current_node = redirector_heredoc_update_lst(data);
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
			if (redirector_fork_and_open_heredoc(data, index,
					counter_heredocs) == ERROR)
			{
				return (ERROR);
			}
			counter_heredocs -= 1;
		}
		index += 1;
	}
	return (EXECUTED);
}
