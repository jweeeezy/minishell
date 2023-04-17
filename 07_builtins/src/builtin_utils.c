/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:46:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/17 14:22:07 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for MACROS

int	is_builtin(int cmd_to_check)
{
	if (cmd_to_check == ECHO
		|| cmd_to_check == REJECTED_ECHO
		|| cmd_to_check == ENV
		|| cmd_to_check == CD
		|| cmd_to_check == PWD
		|| cmd_to_check == EXPORT
		|| cmd_to_check == UNSET
		|| cmd_to_check == EXIT)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
