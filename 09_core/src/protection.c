/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:11:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/27 10:52:13 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argument_protection(t_data *data, int argc, char **argv, char **envp)
{
	g_signal = 1;
	if (argc > 1)
		return (ERROR);
	data->expander = NULL;
	put_to_linked_list_expander(data, envp);
	data->argv = argv;
	data->envp = envp;
	return (EXECUTED);
}
