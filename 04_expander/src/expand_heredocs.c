/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:56:37 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 10:55:39 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for malloc(), free(), NULL
#include "minishell.h"		// needed for t_heredoc
#include <fcntl.h>			// needed for open()
#include <unistd.h>			// needed for close()
#include "libft.h"			// needed for ft_atoi(), ft_strjoin()
#include "libme.h"			// needed for ft_itoa_unsigned_long
#include "redirector.h"	
#include <stdio.h>

char	*expand_heredocs(t_data *data, char *str)
{
	char	**tokens;
	char	*temp;
	int		q;

	q = 0;
	temp = NULL;
	(void) data;
	if (ft_strchr(str, '$') == NULL)
		return (str);
	tokens = tokenizer(str, 0, 0, 0);
	if (tokens == NULL)
		return (str);
	temp = expand_tokens_helper(data, temp, q, tokens);
	if (temp == NULL)
		temp = ft_strdup("");
	split_free(tokens);
	return (free(str), temp);
}
