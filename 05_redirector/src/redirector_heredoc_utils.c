/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/05 14:50:50 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for malloc(), free(), NULL
#include "minishell.h"		// needed for t_heredoc

void	heredoc_clean_lst(t_data *data, int flag_input)
{
	t_heredoc	*current_node;
	t_heredoc	*next;
	int			index;

	index = 0;
	current_node = data->heredoc;
	if (current_node == NULL)
	{
		return ;
	}
	next = current_node->next;
	while (current_node != NULL)
	{
		next = current_node->next;
		if (index == flag_input)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
		}
		else
		{
			close(current_node->fd_pipe[0]); // read end
		}
		close(current_node->fd_pipe[1]); // write end
		// @note mb the other way around if parent immediately writes to pipe
		free(current_node);
		current_node = next;
		index += 1;
	}
}

t_heredoc	*heredoc_get_new_node(void)
{
	t_heredoc	*new_node;

	new_node = malloc (sizeof (t_heredoc));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->fd_pipe = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_heredoc	*heredoc_adad_back(t_heredoc *lst_to_expand, t_heredoc *node_to_add)
{
	if (lst_to_expand == NULL || node_to_add == NULL)
	{
		return (NULL);
	}
	while (lst_to_expand->next != NULL)
	{
		lst_to_expand = lst_to_expand->next;
	}
	lst_to_expand->next = node_to_add;
	return (node_to_add);
}

t_heredoc	*heredoc_get_node_by_index(t_heredoc *lst_to_loop, int index)
{
	if (lst_to_loop == NULL)
	{
		return (NULL);
	}
	if (index < 0)
	{
		while (lst_to_loop->next != NULL)
		{
			lst_to_loop = lst_to_loop->next;
		}
		return (lst_to_loop);
	}
	else
	{
		while (lst_to_loop->next != NULL && index > 0)
		{
			lst_to_loop = lst_to_loop->next;
		}
		return (lst_to_loop);
	}
}

int	heredoc_count_nodes(t_heredoc *lst_to_loop)
{
	int	length;

	length = 0;
	if (lst_to_loop == NULL)
	{
		return (0);
	}
	while (lst_to_loop->next != NULL)
	{
		lst_to_loop = lst_to_loop->next;
		length += 1;
	}
	return (length);
}
