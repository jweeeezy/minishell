/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/12 16:21:28 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for malloc(), free(), NULL
#include "minishell.h"		// needed for t_heredoc
#include <unistd.h>			// needed for open(), close()

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
	char	*temp;

	temp = ft_itoa_unsigned_long((unsigned long int) node_to_edit);
	while (node_to_edit->hash == 0
		&& heredoc_check_duplicate_hash(data->heredoc, node_to_edit) == 1)
	{
		note_to_edit->hash = heredoc_create_hash(temp);
	}
	free(temp);
	temp = ft_itoa_unsigned_long(node_to_edit->hash);
	if (temp == NULL)
	{
		return (ERROR);
	}
	node_to_edit->full_path = ft_strjoin("/tmp/", temp);
	free(temp);
	return (EXECUTED);
}
