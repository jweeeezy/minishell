/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_redirection_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/25 19:36:12 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"		// needed for t_data, MACROS
#include "libft.h"			// needed for ft_split()
#include <stdlib.h>			// needed for free()

#include <stdio.h>

char	*redirector_get_filename(t_data *data, int index, int token_type)
{
	char	*str_filename;

	if (token_type == HERE_DOC)
	{
		return (NULL);
	}
	if (token_type == COMMAND_TO_FILE || token_type == FILE_TO_COMMAND)
	{
		str_filename = ft_strdup(data->combine[index].combined_str + 1);
	}
	else
	{
		str_filename = ft_strdup(data->combine[index].combined_str + 2);
	}
	return (str_filename);
}

int	redirector_find_end_of_command(t_data *data, int index)
{
	if (data->combine[index].command->order_numb == PIPE
		|| data->combine[index].command->order_numb == LAST_PIPE)
	{
		index += 1;
	}
	while (index < data->commands_to_process
		&& data->combine[index].combined_str != NULL)
	{
		if (data->combine[index].command->order_numb == PIPE
			|| data->combine[index].command->order_numb == LAST_PIPE)
		{
			break ;
		}
		index += 1;
	}
	return (index);
}
