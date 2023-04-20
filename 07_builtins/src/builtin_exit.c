/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:32:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/20 16:13:03 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int	rejected_exit(t_data *data, int index)
{
	if (data->combine[index].count_n < 3)
	{
		g_signal = 0;
		data->exit_status = 0;
		return (ERROR);
	}
	else if (data->combine[index].count_n > 4)
	{
		data->exit_status = 1;
		ft_putstr_fd("Too many arguments\n", 2);
		return (ERROR);
	}
	return (EXECUTED);
}

void	builtin_exit(t_data *data, int exit_code, int index)
{
	int	cnt;

	cnt = 0;
	if (rejected_exit(data, index) == ERROR)
		return ;
	exit_code = ft_atoi(data->combine[index].execute[2 + cnt].order_str);
	if (exit_code == 0
		&& data->combine[index].execute[2 + cnt].order_str[0] == '0'
		&& ft_strlen(data->combine[index].execute[2 + cnt].order_str) == 1)
		g_signal = 0;
	else if (exit_code == 0)
	{
		ft_putstr_fd("Terminal Trouble: Not a valid exit\n", 2);
		g_signal = 255;
	}
	else
		g_signal = exit_code % 256;
	data->exit_status = g_signal;
}
