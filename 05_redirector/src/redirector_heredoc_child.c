/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_child.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:48:48 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/01 12:26:00 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>	// needed for readline()
#include <unistd.h>				// needed for close()
#include "minishell.h"			// needed for t_data, MACROS
#include "redirector.h"			// needed for heredoc_lst_clean()
#include "libft.h"				// needed for ft_strlen(), ft_substr()
								// ft_strncmp(), ft_putstr_fd()

static char	*heredoc_get_delimiter(t_data *data, int index)
{
	char	*offset_ptr;
	char	*delimiter;
	size_t	length;

	offset_ptr = data->combine[index].combined_str + 2;
	length = ft_strlen(offset_ptr);
	delimiter = ft_substr(offset_ptr, 0, length);
	return (delimiter);
}

static int	heredoc_loop(t_data *data, t_heredoc *current_node,
	char *heredoc_delimiter, int mode)
{
	char	*heredoc_line;

	heredoc_line = readline("> ");
	if (heredoc_line == NULL)
		return (ERROR);
	if (mode == QUOTED_HEREDOC)
		heredoc_line = expand_heredocs(data, heredoc_line);
	if (heredoc_delimiter != NULL)
	{
		if (ft_strncmp(heredoc_line, heredoc_delimiter,
				ft_strlen(heredoc_delimiter)) == 0
			&& ft_strlen(heredoc_delimiter) == ft_strlen(heredoc_line))
		{
			ft_putstr_fd("\0", current_node->fd);
			free(heredoc_line);
			return (1);
		}
	}
	ft_putstr_fd(heredoc_line, current_node->fd);
	ft_putstr_fd("\n", current_node->fd);
	free(heredoc_line);
	return (EXECUTED);
}

static int	heredoc_open_heredoc(t_data *data, int index, t_heredoc *c_node)
{
	int		return_value;
	char	*heredoc_delimiter;

	return_value = 0;
	if (c_node == NULL)
	{
		heredoc_lst_clean(data);
		return (ERROR);
	}
	heredoc_delimiter = heredoc_get_delimiter(data, index);
	if (heredoc_delimiter == NULL)
	{
		heredoc_lst_clean(data);
		return (ERROR);
	}
	while (1)
	{
		return_value = heredoc_loop(data, c_node, heredoc_delimiter,
				data->combine[index].command->order_numb);
		if (return_value != EXECUTED)
			break ;
	}
	free(heredoc_delimiter);
	return (return_value);
}

static void	heredoc_free_child(t_data *data, t_heredoc *current_node)
{
	close(current_node->fd);
	free_env(data);
	free_t_heredoc(data);
	free_loop(data);
}

void	heredoc_child_routine(t_data *data, int index,
		t_heredoc *current_node, int status)
{
	free_env(data);
	heredoc_signals();
	status = heredoc_open_heredoc(data, index, current_node);
	if (status == ERROR)
	{
		heredoc_free_child(data, current_node);
		exit(ERROR);
	}
	heredoc_free_child(data, current_node);
	exit(EXECUTED);
}
