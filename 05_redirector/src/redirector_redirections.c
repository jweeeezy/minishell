/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:24:34 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/08 14:13:51 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data, MACROS
#include <fcntl.h>		// needed for open()
#include <unistd.h>		// needed for open(), close()
#include <stdio.h>		// needed for printf(), perror()
#include "redirector_private.h"

static int	redirector_assign_outfile(t_data *data, char *str_filename)
{
	if (data->flag_outfile == 1)
	{
		close(data->fd_outfile);
	}
	data->fd_outfile = open(str_filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data->fd_outfile == -1)
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
		close(data->fd_outfile);
	}
	data->fd_outfile = open(str_filename,
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (data->fd_outfile == -1)
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
	t_heredoc	*next_node;

	if (data->flag_heredoc == 1)
	{
		next_node = data->heredoc->next;
		//free(data->heredoc->full_path);
		close(data->heredoc->fd);
		free(data->heredoc);
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
		return (ERROR);
	}
	data->flag_infile = 1;
	data->flag_heredoc = 0;
	free(str_filename);
	return (EXECUTED);
}

static int	redirector_assign_heredoc(t_data *data)
{
	t_heredoc *next_node;

	if (data->flag_heredoc == 1)
	{
		next_node = data->heredoc->next;
	//	free(data->heredoc->full_path);
		close(data->heredoc->fd);
		free(data->heredoc);
		data->heredoc = next_node;
	}
	else if (data->flag_infile == 1)
	{
		close(data->fd_infile);
	}
	data->fd_infile = data->heredoc->fd;
	if (data->heredoc->fd < 0)
	{
		return (ERROR);
	}
	data->flag_heredoc = 1;
	data->flag_infile = 0;
	return (EXECUTED);
}

static int	redirector_crossroads(t_data *data, int index, int flag_redirection)
{
	char	*str_filename;
	int		return_value;

	return_value = 0;
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
	else if (flag_redirection == HERE_DOC)
	{
		free(str_filename);
		return_value = redirector_assign_heredoc(data);
	}
	if (return_value == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

void	redirector_handler_input(t_data *data)
{
	if (data->flag_infile == 1)
	{
		dup2(data->fd_infile, STDIN_FILENO);
	}
}

void	redirector_handler_output(t_data *data)
{
	if (data->flag_outfile == 1)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
	}
}

int	redirector_prehandle_redirections(t_data *data, int counter_redirections)
{
	int	offset;
	int	token_type;
	int	index;			// @note needed ?

	index = 0;
	(void) counter_redirections;
	offset = redirector_find_end_of_command(data, index);
	while (index < offset)
	{
		token_type = data->combine[index].command->order_numb;
		if (token_type == COMMAND_TO_FILE
			|| token_type == FILE_TO_COMMAND
			|| token_type == SHELL_REDIRECTION
			|| token_type == HERE_DOC)
		{
			if (redirector_crossroads(data, index, token_type) == ERROR)
			{
				return (ERROR);
			}
			data->combine[index].command->order_numb = WHITE;
		}
		index += 1;
	}
	return (EXECUTED);
}

// @note close file descriptors!
// @note free array/string
