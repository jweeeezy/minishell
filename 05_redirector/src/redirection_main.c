/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:24:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/30 11:00:29 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include <stdio.h>		// needed for printf()
#include <fcntl.h>		// needed for open()

static char	*redirector_get_filename(t_data *data, int index)
{
	char 	**split_array;
	char	*str_filename;

	split_array = ft_split(data->combine[index].combined_str, ' ');
	if (split_array == NULL)
		return (NULL);
	str_filename = split_array[1];
	free(split_array[0]);
	free(split_array);
	return (str_filename);
}

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

static int	redirector_assign_outfile(t_data *data, char *str_filename)
{
	data->fd_outfile = open(str_filename,
			O_WRONLY | O_CREAT | 0_TRUNC, 0666);
	if (fd == -1)
	{
		perror("open");
		free(str_filename);
		return (ERROR);
	}
	data->flag_outfile = 1;
	free(str_filename);
	return (EXECUTED);
}

static int	redirector_assign_outfile_append(t_data *data, char *str_filename)
{
	data->fd_outfile_append = open(str_filename,
			O_WRONLY | O_CREAT | 0_APPEND, 0666);
	if (fd == -1)
	{
		perror("open");
		free(str_filename);
		return (ERROR);
	}
	data->flag_outfile_append = 1;
	free(str_filename);
	return (EXECUTED);
}

static int	redirector_assign_infile(t_data *data, char *str_filename)
{
	data->fd_infile = open(str_filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free(str_filename);
		return (ERROR);
	}
	data->flag_infile = 1;
	free(str_filename);
	return (EXECUTED);

}

int	redirector_crossroads(t_data *data, int index, int flag_redirection)
{
	char	*str_filename;

	str_filename = redirector_get_filename(data, index);
	if (str_filename == NULL)
	{
		return (ERROR);
	}
	if (flag_redirection == COMMAND_TO_FILE)
	{
		if (redirector_assign_outfile(data, str_filename) == -1)
		{
			return (ERROR);
		}
	}
	else if (flag_redirection == FILE_TO_COMMAND)
	{
		if (redirector_assign_infile(data, str_filename) == ERROR)
		{
			return (ERROR);
		}
	}
	else if (flag_redirection == SHELL_REDIRECTION)
	{

		if (redirector_assign_outfile_append(data, str_filename) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}

int	redirector_main(t_data *data, int index)
{
	int	offset;
	int	token_type;

	offset = redirector_find_offset_to_next_pipe(data, index);
	while (index < offset)
	{
		token_type = data->combine[index].command->order_numb;
		if (token_type == COMMAND_TO_FILE
			|| token_type == FILE_TO_COMMAND
			|| token_type == SHELL_REDIRECTION)
		{
			if (redirector_crossroads(data, intex, token_type) == ERROR)
			{
				return (ERROR);
			}
			token_type = WHITE;
		}
		index += 1;
	}
	return (EXECUTED);
}

// @note close file descriptors!
// @note free array/string
