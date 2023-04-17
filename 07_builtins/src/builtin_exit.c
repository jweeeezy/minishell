/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:32:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/16 16:33:41 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	copy_of_minitalk(int pid, int c)
{
	int	base;

	base = 256;
	while (base > 1)
	{
		base = base / 2;
		if (((c / base) % 2) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
	}
}

void	builtin_exit(t_data *data, int exit_code, int index)
{
	if (data->commands_to_process - 1 != index)
		return ;
	if (data->combine[index].count_n > 3)
	{
		printf("Terminal Troble: too many arguments\n");
		return ;
	}
	if (data->combine[0].count_n == 3)
	{
		exit_code = ft_atoi(data->combine[0].execute[2].order_str);
		if (exit_code == 0 && data->combine[0].execute[2].order_str[0] == '0'
			&& ft_strlen(data->combine[0].execute[2].order_str) == 1)
			g_signal = 0;
		else if (exit_code == 0)
		{
			printf("Terminal Trouble: %s: Not a valid input\n",
				data->combine[0].execute[2].order_str);
			g_signal = 0;
		}
		else
			g_signal = exit_code % 256;
	}
	else
		g_signal = 0;
	copy_of_minitalk(data->pid, g_signal);
}
