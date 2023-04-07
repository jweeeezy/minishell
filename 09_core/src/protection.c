/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:11:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/07 15:19:05 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argument_protection(t_data *data, int argc, char **argv, char **envp)
{
	g_signal = 1;
	if (argc > 1)
		return (ERROR);
	data->argv = argv;
	data->envp = envp;
	//@note sure how to set them at first
	data->heredoc = NULL;
	data->flag_infile = 0;
	data->flag_outfile = 0;
	data->fd_infile = 0;
	data->fd_outfile = 1;
	return (EXECUTED);
}
