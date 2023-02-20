/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:21:09 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/04 11:42:55 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_yeet_blanks(char const *s, char c, int start_pos, int mode)
{
	while (*(s + start_pos) == c && *(s + start_pos) != '\0' && mode == 0)
		start_pos++;
	while (*(s + start_pos) != c && *(s + start_pos) != '\0' && mode == 1)
		start_pos++;
	return (start_pos);
}

int	ft_get_words(char const *s, char c, int start_pos, int len)
{
	int	words;
	int	temp;

	words = 0;
	while (start_pos != len)
	{
		start_pos = ft_yeet_blanks(s, c, start_pos, 0);
		temp = start_pos;
		start_pos = ft_yeet_blanks(s, c, start_pos, 1);
		if (start_pos == temp)
			return (words);
		words++;
	}
	return (words);
}

char	*ft_create_word(const char *s, int pos_x, int pos_y)
{
	char	*word;
	int		cnt;

	cnt = 0;
	word = ft_calloc((pos_y - pos_x + 1), sizeof(char));
	if (word == NULL)
		return (NULL);
	while (pos_x < pos_y)
	{
		*(word + cnt) = *(s + pos_x);
		pos_x++;
		cnt++;
	}
	return (word);
}

char	**ft_free(char **ptr)
{
	int	cnt;

	cnt = 0;
	while (*(ptr + cnt) != NULL)
	{
		free(*(ptr + cnt));
		cnt++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		pos;
	int		cnt;
	char	**dest;
	char	*temp;

	if (s == NULL)
		return (NULL);
	words = ft_get_words(s, c, 0, ft_strlen((char *)s));
	dest = ft_calloc((words + 1), sizeof(char *));
	if (dest == NULL)
		return (NULL);
	cnt = 0;
	pos = 0;
	while (cnt < words)
	{
		pos = ft_yeet_blanks(s, c, pos, 0);
		temp = ft_create_word(s, pos, ft_yeet_blanks(s, c, pos, 1));
		pos = ft_yeet_blanks(s, c, pos, 1);
		if (temp == NULL)
			return (ft_free(dest));
		*(dest + cnt) = temp;
		cnt++;
	}
	return (dest);
}
