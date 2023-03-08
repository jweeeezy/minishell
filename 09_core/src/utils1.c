/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:01:08 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/08 14:43:08 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	utils_check_for_chars(t_data *data, int segment)
// {
// 	if (data->args[segment] || ft_strchr("<>|", data->args[segment]))
// 		return (ADD);
// 	return (EXECUTED);
// }

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (ADD);
	return (EXECUTED);
}

int	is_pipe(int c)
{
	if (c == PIPE || c == SHELL_REDIRECTION || c == HERE_DOC
		|| c == FILE_TO_COMMAND || c == COMMAND_TO_FILE)
		return (ADD);
	return (EXECUTED);
}
