/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_redirection_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/27 12:53:12 by jwillert         ###   ########.fr       */
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

void	handle_open_error(t_data *data, char *str_filename,
		int flag_indirection)
{
	if (data->flag_printed == 0)
	{
		perror("open");
		data->flag_printed = 1;
	}
	if (flag_indirection == 0)
	{
		data->exit_status = 1;
	}
	else
	{
		data->fd_infile = -100;
	}
	if (str_filename != NULL)
	{
		free(str_filename);
	}
}
