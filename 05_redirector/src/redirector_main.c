/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:24:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/30 13:09:38 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include <fcntl.h>		// needed for open()

static int	redirector_assign_outfile(t_data *data, char *str_filename)
{
	if (data->flag_outfile == 1)
	{
		close(fd_outfile);
	}
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
	if (data->flag_outfile == 1)
	{
		close(fd_outfile);
	}
	data->fd_outfile = open(str_filename,
			O_WRONLY | O_CREAT | 0_APPEND, 0666);
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

static int	redirector_assign_infile(t_data *data, char *str_filename)
{
	if (data->flag_infile == 1)
	{
		close(fd_infile);
	}
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

static int	redirector_crossroads(t_data *data, int index, int flag_redirection)
{
	char	*str_filename;
	int		return_value;

	str_filename = redirector_get_filename(data, index);
	if (str_filename == NULL)
	{
		return (ERROR);
	}
	if (flag_redirection == COMMAND_TO_FILE)
	{
		return_value = redirector_assign_outfile(data, str_filename);
	}
	else if (flag_redirection == FILE_TO_COMMAND)
	{
		return_value = redirector_assign_infile(data, str_filename);
	}
	else if (flag_redirection == SHELL_REDIRECTION)
	{
		return_value = redirector_assign_outfile_append(data, str_filename);
	}
	if (return_value == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

void	redirector_handler_input(t_data *data, int index)
{
	if (flag_infile == 1)
	{
		dup2(data->fd_infile, STDIN_FILENO);
	}
}

void	redirector_handler_output(t_data *data, int index)
{
	if (flag_outfile == 1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
	}
}

int	redirector_prehandler(t_data *data, int index)
{
	int	offset;
	int	token_type;

	offset = redirector_find_end_of_command(data, index);
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
