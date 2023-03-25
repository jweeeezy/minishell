/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:46:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/25 15:54:19 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_combine cmd_to_check)
{
	if (cmd_to_check == ECHO
		|| cmd_to_check == CD
		|| cmd_to_check == LS
		|| cmd_to_check == PWD
		|| cmd_to_check == EXPORT
		|| cmd_to_check == UNSET
		|| cmd_to_check == EXIT)
		return (1);
	else
		return (0);
}
