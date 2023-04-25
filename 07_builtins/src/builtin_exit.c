/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:32:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/25 12:14:05 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "libme.h"
#include <limits.h>
#include "limits.h"

static int	ft_isdigit_u(int c_to_check)
{
	if (c_to_check >= '0' && c_to_check <= '9')
		return (1);
	if (c_to_check == '-' || c_to_check == '+')
		return (1);
	return (0);
}

int	rejected_exit(t_data *data, int index)
{
	if (data->combine[index].count_n < 3)
	{
		g_signal = 0;
		data->exit_status = 0;
		return (ERROR);
	}
	else if (ft_isdigit_u(data->combine[index].execute[2].order_str[0]) == 0)
	{
		g_signal = 0;
		data->exit_status = 255;
		ft_putstr_fd("Numberic argument required\n", 2);
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
	exit_code = ft_atoi_long(data->combine[index].execute[2 + cnt].order_str);
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
