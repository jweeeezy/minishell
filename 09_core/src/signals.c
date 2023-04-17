/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:20:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/16 15:27:31 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <unistd.h>

void	ft_printer(int sig)
{
	static int	result;
	static int	pow;

	if (pow == 0 || pow == 1)
		pow = 256;
	pow = pow / 2;
	if (sig == SIGUSR1)
		result = result + pow;
	if (pow == 1)
	{
		g_signal = result;
		result = 0;
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGTERM)
		g_signal = 0;
}
