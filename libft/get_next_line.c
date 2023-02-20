/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:00:37 by kvebers           #+#    #+#             */
/*   Updated: 2022/12/06 12:35:58 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_temp(char *temp, int fd, int read_mode)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while ((ft_strchr2(temp, '\n') == NULL) && read_mode != 0)
	{
		read_mode = read(fd, buffer, BUFFER_SIZE);
		if (read_mode == -1)
			return (free(buffer), free(temp), NULL);
		*(buffer + read_mode) = '\0';
		temp = ft_strjoin2(temp, buffer, 0, 0);
		if (*temp == '\0')
			return (free(temp), free(buffer), NULL);
	}
	return (free(buffer), temp);
}

char	*ft_line(char *temp, int cnt)
{
	char	*line;

	while (*(temp + cnt) != '\n' && *(temp + cnt) != '\0')
		cnt++;
	line = malloc(sizeof(char) * (cnt + 2));
	if (line == NULL)
		return (free(temp), NULL);
	cnt = 0;
	while ((*(temp + cnt) != '\n' ) && (*(temp + cnt) != '\0'))
	{
		*(line + cnt) = *(temp + cnt);
		cnt++;
	}
	*(line + cnt) = *(temp + cnt);
	*(line + cnt + 1) = '\0';
	return (line);
}

char	*ft_yeet_lines(char *temp, int cnt1, int cnt2)
{
	char	*new_temp;

	if (ft_strchr2(temp, '\n') == NULL)
		return (free(temp), NULL);
	while (*(temp + cnt1) != '\n')
		cnt1++;
	if (*(temp + cnt1) == '\0')
		return (free(temp), NULL);
	while (*(temp + cnt1 + cnt2) != '\0')
		cnt2++;
	new_temp = malloc(sizeof(char) * (cnt2 + 1));
	if (new_temp == NULL)
		return (free(temp), NULL);
	cnt2 = 0;
	while (*(temp + cnt1 + cnt2) != '\0')
	{
		*(new_temp + cnt2) = *(temp + cnt1 + cnt2 + 1);
		cnt2++;
	}
	return (free(temp), new_temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	temp[fd] = get_temp(temp[fd], fd, 1);
	if (temp[fd] == NULL)
		return (NULL);
	line = ft_line(temp[fd], 0);
	if (ft_strchr2(line, '\n') == NULL && ft_strlen(line) == 0)
		return (free(line), free(temp[fd]), NULL);
	temp[fd] = ft_yeet_lines(temp[fd], 0, 0);
	return (line);
}
