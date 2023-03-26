/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:46:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/26 16:24:03 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(int cmd_to_check)
{
	if (cmd_to_check == ECHO
		|| cmd_to_check == ECHO_N
		|| cmd_to_check == ENV
		|| cmd_to_check == CD
		|| cmd_to_check == PWD
		|| cmd_to_check == EXPORT
		|| cmd_to_check == UNSET
		|| cmd_to_check == EXIT)
		return (1);
	else
		return (0);
}