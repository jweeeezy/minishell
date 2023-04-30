/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_lst_update.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:02:13 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for malloc(), free(), NULL
#include <fcntl.h>			// needed for open()
#include <unistd.h>			// needed for close()
#include "minishell.h"		// needed for t_heredoc
#include "libft.h"			// needed for ft_atoi(), ft_strjoin()
#include "libme.h"			// needed for ft_itoa_unsigned_long
#include "redirector.h"		// needed for heredoc_lst_*

static int	heredoc_check_duplicate_hash(t_heredoc *head,
				t_heredoc *node_to_compare)
{
	while (head != NULL)
	{
		if (head != node_to_compare && node_to_compare->hash == head->hash)
		{
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static int	heredoc_create_hash(char *string_to_hash)
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

static int	heredoc_get_full_path(t_data *data, t_heredoc *node_to_edit)
{
	char	*temp;

	temp = ft_itoa_unsigned((unsigned long int) node_to_edit);
	while (node_to_edit->hash == 0
		&& heredoc_check_duplicate_hash(data->heredoc, node_to_edit) != 1)
	{
		node_to_edit->hash = heredoc_create_hash(temp);
	}
	free(temp);
	temp = ft_itoa_unsigned(node_to_edit->hash);
	if (temp == NULL)
	{
		return (ERROR);
	}
	node_to_edit->full_path = ft_strjoin("/tmp/", temp);
	free(temp);
	return (EXECUTED);
}

static int	heredoc_create_file(t_data *data, t_heredoc *node_to_edit)
{
	if (heredoc_get_full_path(data, node_to_edit) == ERROR)
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

t_heredoc	*heredoc_lst_update(t_data *data)
{
	t_heredoc	*node_to_edit;

	if (data->heredoc == NULL)
	{
		data->heredoc = heredoc_lst_get_new_node();
		node_to_edit = data->heredoc;
	}
	else
	{
		node_to_edit = heredoc_lst_get_and_add_last(data->heredoc,
				heredoc_lst_get_new_node());
	}
	if (node_to_edit == NULL)
	{
		return (NULL);
	}
	if (heredoc_create_file(data, node_to_edit) == ERROR)
	{
		free(node_to_edit);
		return (NULL);
	}
	return (node_to_edit);
}
