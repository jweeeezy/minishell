/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:11:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/16 14:10:37 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	argument_protection(t_data *data, int argc, char **argv, char **envp)
{
	g_signal = 256;
	data->pid = getpid();
	if (argc > 1)
		return (ERROR);
	data->argv = argv;
	data->envp = envp;
	data->heredoc = NULL;
	data->flag_infile = 0;
	data->flag_outfile = 0;
	data->flag_heredoc = 0;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	return (EXECUTED);
}
