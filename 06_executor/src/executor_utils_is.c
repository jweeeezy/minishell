/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_is.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:20:28 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/30 22:33:35 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_combine, MAROS
#include <unistd.h>		// needed for access()
#include "libft.h"		// needed for ft_strdup()

int	executor_is_heredoc(t_combine *cmd)
{
	if (cmd->command->order_numb == HERE_DOC)
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

int	executor_is_cmd_path_valid(t_execute *cmd)
{
	if (access(cmd->order_str, X_OK) == 0)
	{
		cmd->full_path = ft_strdup(cmd->order_str);
		return (EXTERN);
	}
	return (COMMAND_NOT_FOUND);
}
