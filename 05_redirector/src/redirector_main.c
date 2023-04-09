/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:43:42 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/08 14:57:19 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"			// needed for t_data, MACROS
#include "executor_private.h"	// needed for executor_*()
#include "redirector_private.h"	// needed for redirector_*()

int	redirector(t_data *data)
{
	int	heredocs;
	int	redirections;

	heredocs = executor_count_heredocs(data);
	redirections = executor_count_redirections(data);
	if (heredocs > 0)
	{
		if (redirector_prehandle_heredocs(data, heredocs) == ERROR)
		{
			return (ERROR);
		}
	}
	// if (redirections > 0)
	// {
	// 	if (redirector_prehandle_redirections(data, redirections) == ERROR)
	// 	{
	// 		return (ERROR);
	// 	}
	// }
	debug_print_t_combine(data);
	return (EXECUTED);
}
