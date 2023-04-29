/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:20:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/28 14:48:16 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>

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

void	signals(void)
{
	struct termios		term_settings;

	tcgetattr(1, &term_settings);
	term_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &term_settings);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
}

void	child_handler(int sig)
{
	if (sig == SIGINT)
		printf("^C\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	child_signals(void)
{
	signal(SIGINT, child_handler);
	signal(SIGTERM, child_handler);
	signal(SIGQUIT, child_handler);
}

void	heredoc_signals(void)
{
	signal(SIGINT, here_signals);
	signal(SIGTERM, here_signals);
	signal(SIGQUIT, SIG_IGN);
}
