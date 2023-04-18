/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:40:00 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/18 09:40:41 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	gnl_strlen(const char *string)
{
	size_t	index;

	index = 0;
	if (string == NULL)
		return (0);
	while (string[index] != '\0')
		index++;
	return (index);
}

size_t	gnl_strlcpy(char *string_target,
		char *string_source, size_t size_needed)
{
	size_t	index;

	index = 0;
	if (size_needed <= 0)
		return (gnl_strlen(string_source));
	while (index < (size_needed - 1) && string_source[index] != '\0')
	{
		string_target[index] = string_source[index];
		index++;
	}
	if (index < size_needed)
		string_target[index] = '\0';
	while (string_source[index] != '\0')
		index++;
	return (index);
}

size_t	gnl_strlcat(char *string_target,
		char *string_source, size_t size_needed)
{
	size_t	offset;
	size_t	size_target;
	size_t	size_source;

	size_target = gnl_strlen(string_target);
	size_source = gnl_strlen(string_source);
	if (size_target > size_needed)
		return (size_source + size_needed);
	offset = size_target;
	while (*string_source != '\0' && offset + 1 < size_needed)
	{
		string_target[offset] = *string_source;
		offset++;
		string_source++;
	}
	string_target[offset] = '\0';
	return (size_source + size_target);
}

char	*gnl_strjoin(char *string_first, char *string_second)
{
	char	*string_new;
	size_t	size;

	if (string_first == NULL)
	{
		string_first = malloc (sizeof (char) * 1);
		if (string_first == NULL)
			return (NULL);
		string_first[0] = '\0';
	}
	if (string_first == NULL)
		return (NULL);
	if (*string_second == '\0')
		return (string_first);
	size = gnl_strlen(string_first) + gnl_strlen(string_second) + 1;
	string_new = (char *) malloc (size * sizeof (char));
	if (string_new == NULL)
		return (NULL);
	gnl_strlcpy(string_new, string_first, size);
	gnl_strlcat(string_new, string_second, size);
	free(string_first);
	return (string_new);
}
