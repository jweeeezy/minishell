/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_is.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:20:28 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/09 15:07:45 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_combine, MAROS
#include <unistd.h>		// needed for access()
#include "libft.h"		// needed for ft_strdup()
#include "libme.h"

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

int	executor_is_cmd_path_valid(t_combine *cmd)
{
	char	**array;

	array = ft_split(cmd->combined_str, ' ');
	if (array == NULL)
	{
		return (ERROR);
	}
	if (access(array[0], X_OK) == 0)
	{
		cmd->first_element = ft_strdup(array[0]);
		ft_array_str_free(array);
		return (EXTERN);
	}
	cmd->first_element = ft_strdup(array[0]);
	ft_array_str_free(array);
	return (COMMAND_NOT_FOUND);
}
