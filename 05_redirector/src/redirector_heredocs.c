/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:21:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/26 17:34:54 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector.h"			// needed for heredoc_*()
#include "executor.h"			// needed for executor_count_heredocs()
#include "minishell.h"			// needed for t_data
#include "libft.h"				// needed for ft_strncmp(), ft_strlen(),
								// ft_putstr_fd()
#include <fcntl.h>				// needed for open()
#include <unistd.h>				// needed for close(), fork()
#include <readline/readline.h>	// needed for readline()
#include <readline/history.h>	// @note heredoc history?
#include <sys/wait.h>
//#include <sys/types.h>

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

static int	heredoc_loop(t_heredoc *current_node, char *heredoc_delimiter)
{
	char	*heredoc_line;

	heredoc_line = readline("> ");
	//printf("delimiter: [%s]\n", heredoc_delimiter);
	if (heredoc_line == NULL)
	{
		return (ERROR);
	}
	if (heredoc_delimiter != NULL)
	{
		if (ft_strncmp(heredoc_line, heredoc_delimiter,
				ft_strlen(heredoc_delimiter)) == 0)
		{
			ft_putstr_fd("\0", current_node->fd);
			free(heredoc_line);
			return (1);
		}
	}
	ft_putstr_fd(heredoc_line, current_node->fd);
	ft_putstr_fd("\n", current_node->fd);
	return (EXECUTED);
}

static int	heredoc_open_heredoc(t_data *data, int index,
			t_heredoc *current_node)
{
	int		return_value;
	char	*heredoc_delimiter;

	return_value = 0;
	if (current_node == NULL)
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
		return_value = heredoc_loop(current_node, heredoc_delimiter);
		if (return_value != EXECUTED)
		{
			break ;
		}
	}
	free(heredoc_delimiter);
	return (return_value);
}

static int	heredoc_fork_and_open(t_data *data, int index)
{
	t_heredoc	*current_node;
	int			id;

	current_node = heredoc_lst_update(data);
	if (current_node == NULL)
	{
		return (ERROR);
	}
	id = fork();
	if (id == 0)
	{
		if (heredoc_open_heredoc(data, index, current_node) == ERROR)
		{
			exit(ERROR);
		}
		close(current_node->fd);
		exit(EXECUTED);
	}
	else
	{
		wait(NULL);			// @note waitpid instead? test with piping into ./minishell
		close(current_node->fd);
	}
	return (EXECUTED);
}

int	redirector_prehandle_heredocs(t_data *data)
{
	int	index;
	int	counter_heredocs;

	index = 0;
	counter_heredocs = executor_count_heredocs(data);
	while (index < data->commands_to_process && counter_heredocs > 0)
	{
		if (data->combine[index].command->order_numb == HERE_DOC)
		{
			if (heredoc_fork_and_open(data, index) == ERROR)
			{
				return (ERROR);
			}
			counter_heredocs -= 1;
		}
		index += 1;
	}
	return (EXECUTED);
}

//	@note delimiter doesnt work correctly
//	@note heredoc doesnt work correctly
