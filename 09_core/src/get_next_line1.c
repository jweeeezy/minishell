/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:41:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/18 09:42:01 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static char	gnl_search_char(char *string_to_search, char char_to_search)
{
	size_t	index;

	index = 0;
	if (string_to_search == NULL)
		return (0);
	while (string_to_search[index] != '\0')
	{
		if (string_to_search[index] == char_to_search)
			return (1);
		index++;
	}
	return (0);
}

static char	*gnl_extract_newline(char *buffer_save)
{
	size_t	index;
	char	*buffer_extract;

	index = 0;
	if (buffer_save == NULL || buffer_save[index] == '\0')
		return (NULL);
	while (buffer_save[index] != '\0' && buffer_save[index] != '\n')
		index++;
	buffer_extract = malloc (sizeof (char) * (index + 2));
	if (buffer_extract == NULL)
		return (NULL);
	index = 0;
	while (buffer_save[index] != '\0' && buffer_save[index] != '\n')
	{
		buffer_extract[index] = buffer_save[index];
		index++;
	}
	if (buffer_save[index] == '\n')
	{
		buffer_extract[index] = buffer_save[index];
		index++;
	}
	buffer_extract[index] = '\0';
	return (buffer_extract);
}

static char	*gnl_adjust_buffer(char *buffer_to_adjust)
{
	char	*buffer_adjusted;
	size_t	offset;
	size_t	index;

	offset = 0;
	while (buffer_to_adjust[offset] != '\0' && buffer_to_adjust[offset] != '\n')
		offset++;
	if (buffer_to_adjust[offset] == '\0')
	{
		free (buffer_to_adjust);
		return (NULL);
	}
	buffer_adjusted = malloc (sizeof (char)
			* (gnl_strlen(buffer_to_adjust) - offset + 1));
	if (buffer_adjusted == NULL)
		return (NULL);
	offset++;
	index = 0;
	while (buffer_to_adjust[offset] != '\0')
		buffer_adjusted[index++] = buffer_to_adjust[offset++];
	buffer_adjusted[index] = '\0';
	free(buffer_to_adjust);
	return (buffer_adjusted);
}

static char	*gnl_read_until_newline(int fd, char *buffer_static)
{
	char	*buffer_read;
	int		read_return;

	buffer_read = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if (buffer_read == NULL)
		return (NULL);
	read_return = 1;
	while (read_return != 0 && gnl_search_char(buffer_static, '\n') == 0)
	{
		read_return = read(fd, buffer_read, BUFFER_SIZE);
		if (read_return == -1)
		{
			free(buffer_read);
			return (NULL);
		}
		buffer_read[read_return] = '\0';
		buffer_static = gnl_strjoin(buffer_static, buffer_read);
	}
	free(buffer_read);
	return (buffer_static);
}

char	*get_next_line(int fd)
{
	static char	*buffer_static[OPEN_MAX];
	char		*buffer_return;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer_static[fd] = gnl_read_until_newline(fd, buffer_static[fd]);
	if (buffer_static[fd] == NULL)
		return (NULL);
	buffer_return = gnl_extract_newline(buffer_static[fd]);
	buffer_static[fd] = gnl_adjust_buffer(buffer_static[fd]);
	return (buffer_return);
}
