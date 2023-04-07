/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_main_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:43:42 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/07 16:24:18 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor_private.h"	// needed for executor_*()

int	redirector(t_data *data)
{
	int	heredocs;
	int	redirections;
	
	heredocs = executor_count_heredocs(data->combine);
	redirections = executor_count_redirection(data->combine);
	if (heredocs > 0)
	{
		if (redirector_prehandle_heredocs(data, heredocs) == ERROR)
		{
			return (ERROR);
		}
		heredoc_child_close_fd(data, heredoc_get_node_by_index(data->heredoc,
				   	LAST);
	}
	if (redirections > 0)
	{
		if (redirector_prehandle_redirections(data, redirections) == ERROR)
		{
			return (ERROR);
		}
	}
	return (EXECUTED);
}
