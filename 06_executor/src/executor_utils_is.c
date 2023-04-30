/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_is.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:20:28 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:15:48 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_combine, MAROS
#include <unistd.h>		// needed for access()
#include "libft.h"		// needed for ft_strdup()

int	executor_is_heredoc(t_combine *cmd)
{
	if (cmd->command->order_numb == HERE_DOC
		|| cmd->command->order_numb == QUOTED_HEREDOC)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	executor_is_redirection(t_combine *cmd)
{
	if (cmd->command->order_numb == COMMAND_TO_FILE
		|| cmd->command->order_numb == FILE_TO_COMMAND)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	executor_is_pipe(t_combine *cmd)
{
	if (cmd->command->order_numb == PIPE
		|| cmd->command->order_numb == LAST_PIPE)
		return (1);
	else
	{
		return (0);
	}
}

int	executor_is_t_combine_advanceable(t_data *data, int offset)
{
	if (offset < data->commands_to_process
		&& data->combine[offset].combined_str != NULL
		&& data->combine[offset].command->order_numb != PIPE
		&& data->combine[offset].command->order_numb != LAST_PIPE)
	{
		return (1);
	}
	return (0);
}
