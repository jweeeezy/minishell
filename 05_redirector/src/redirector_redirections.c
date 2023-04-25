/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:24:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/25 19:37:43 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include <fcntl.h>		// needed for open()
#include <unistd.h>		// needed for close(), free(), NULL
#include <stdio.h>		// needed for perror()
#include "redirector.h"	// needed for redirector_*()

static int	redirector_assign_outfile(t_data *data, int flag_redirection,
				char *str_filename)
{
	if (data->flag_outfile == 1)
	{
		close(data->fd_outfile);
	}
	if (flag_redirection == COMMAND_TO_FILE)
	{
		data->fd_outfile = open(str_filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else if (flag_redirection == SHELL_REDIRECTION)
	{
		data->fd_outfile = open(str_filename,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	if (data->fd_outfile == -1)
	{
		perror("open");
		free(str_filename);
		return (EXECUTED);
	}
	data->flag_outfile = 1;
	free(str_filename);
	return (EXECUTED);
}
//	@todo differentiate between ERROR and FILE NOT FOUND

static int	redirector_assign_infile(t_data *data, char *str_filename)
{
	t_heredoc	*next_node;

	if (data->flag_heredoc == 1)
	{
		next_node = data->heredoc->next;
		free(data->heredoc->full_path);
		free(data->heredoc);
		close(data->fd_infile);
		data->heredoc = next_node;
	}
	else if (data->flag_infile == 1)
	{
		close(data->fd_infile);
	}
	data->fd_infile = open(str_filename, O_RDONLY);
	if (data->fd_infile == -1)
	{
		perror("open");
		free(str_filename);
		return (EXECUTED);
	}
	data->flag_heredoc = 0;
	data->flag_infile = 1;
	free(str_filename);
	return (EXECUTED);
}

static int	redirector_assign_heredoc(t_data *data)
{
	t_heredoc	*next_node;

	if (data->flag_heredoc == 1)
	{
		next_node = data->heredoc->next;
		free(data->heredoc->full_path);
		free(data->heredoc);
		close(data->fd_infile);
		data->heredoc = next_node;
	}
	else if (data->flag_infile == 1)
	{
		close(data->fd_infile);
	}
	data->fd_infile = open(data->heredoc->full_path, O_RDONLY);
	if (data->fd_infile == -1)
	{
		perror("open");
		return (ERROR);
	}
	data->flag_heredoc = 1;
	data->flag_infile = 0;
	return (EXECUTED);
}

static int	redirector_crossroads(t_data *data, int flag_redirection,
				char *str_filename)
{
	int		return_value;

	return_value = 0;
	if (str_filename == NULL && flag_redirection != HERE_DOC)
	{
		return (ERROR);
	}
	if (flag_redirection == COMMAND_TO_FILE
		|| flag_redirection == SHELL_REDIRECTION)
	{
		return_value = redirector_assign_outfile(data, flag_redirection,
				str_filename);
	}
	else if (flag_redirection == FILE_TO_COMMAND)
	{
		return_value = redirector_assign_infile(data, str_filename);
	}
	else if (flag_redirection == HERE_DOC)
	{
		return_value = redirector_assign_heredoc(data);
	}
	return (return_value);
}

int	redirector_handle_redirections(t_data *data, int index)
{
	int	offset;
	int	token_type;

	offset = redirector_find_end_of_command(data, index);
	while (index < offset)
	{
		token_type = data->combine[index].command->order_numb;
		if (token_type == COMMAND_TO_FILE
			|| token_type == FILE_TO_COMMAND
			|| token_type == SHELL_REDIRECTION
			|| token_type == HERE_DOC)
		{
			if (redirector_crossroads(data, token_type,
					redirector_get_filename(data, index, token_type)) == ERROR)
			{
				return (ERROR);
			}
			data->combine[index].command->order_numb = WHITE;
		}
		index += 1;
	}
	return (EXECUTED);
}
