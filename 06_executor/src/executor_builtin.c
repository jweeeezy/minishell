/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:31:13 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/27 16:34:52 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_data

int	executor_builtin(t_data *data, int **fd_pipes, int index)
{
	if (data->combine[index].command->order_numb == ECHO)
		echo(data->combine[index]);
	else if (data->combine[index].command->order_numb == EXIT
		&& data->commands_to_process == 1)
		g_signal = 0;
	else if (data->combine[index].command->order_numb == PWD)
	{
		if (builtin_pwd() == ERROR)
			return (ERROR);
	}
	else if (data->combine[index].command->order_numb == ECHO_N)
		echo_n(data->combine[index]);
	else if (data->combine[index].command->order_numb == ENV)
		env(data);
	ft_dummy(data);
	ft_dummy(fd_pipes);
	ft_dummy(&index);
	return (EXECUTED);
}
