/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:10:22 by kvebers           #+#    #+#             */
/*   Updated: 2022/10/27 11:22:22 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_trim_cord(char *s1, char *set, int lch)
{
	int	bools;
	int	cnt;
	int	s1_len;

	s1_len = ft_strlen(s1);
	bools = 1;
	cnt = 0;
	while (bools != 0 && cnt < s1_len)
	{
		bools = 0;
		if (ft_strchr(set, *(s1 + cnt)) != 0 && lch == 1)
			bools = 1;
		if (ft_strchr(set, *(s1 + s1_len - cnt - 1)) != 0 && lch == 0)
			bools = 1;
		cnt++;
	}
	return (cnt - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		f_trim;
	int		b_trim;
	int		len;
	char	*dest;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen((char *)s1);
	f_trim = ft_trim_cord((char *)s1, (char *)set, 1);
	b_trim = ft_trim_cord((char *)s1, (char *)set, 0);
	if (len - f_trim - b_trim <= 0)
		len = 1;
	else
		len = len - f_trim - b_trim + 1;
	dest = ft_calloc((len), sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1 + f_trim, len);
	return (dest);
}
