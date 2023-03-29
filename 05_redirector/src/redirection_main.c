/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:24:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/29 22:47:09 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include <stdio.h>		// needed for printf()

static int	redirector_find_offset_to_next_pipe(t_data *data, int index)
{
	while (index < data->commands_to_process)
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

static void	redirector_overwrite_infile(t_data *data, int index, int offset)
{
	ft_dummy(&offset);
	printf("file name: %s\n", data->combine[index].command->order_str);
}

int	redirector_main(t_data *data, int index)
{
	int	offset;

	offset = redirector_find_offset_to_next_pipe(data, index);
	printf("offset: %d\n", offset);
	while (index < offset)
	{
		if (data->combine[index].command->order_numb == COMMAND_TO_FILE)
		{
			redirector_overwrite_infile(data, index + 1, offset);
			data->combine[index].command->order_numb = WHITE;
			data->flag_infile = 1;
		}
//		else if (data->combine[index].command->order_numb == COMMAND_TO_FILE)
		//{
		//	redirector_overwrite_outfile(data, index, offset);
		//	data->outfile = 1;
		//}
		index += 1;
	}
	return (EXECUTED);
}

// @note filename always on the right side of the redirection
// @note set redirection and filename to order_numb = 2
