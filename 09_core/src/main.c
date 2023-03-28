/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/28 21:58:41 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <unistd.h>
#include <termios.h>
#include <signal.h>

static int	history(t_data *data)
{
	data->line = readline("Terminal Troublemakers: ");
	if (data->line == NULL)
		return (ERROR);
	else if (data->line)
	{
		add_history(data->line);
		if (lexer(data) == ERROR)
			return (free(data->line), ERROR);
	}
	return (EXECUTED);
}

static void	check_leaks(void)
{
	if (DEBUG)
		system ("leaks minishell");
}

void	signals(void)
{
	struct termios	term_settings;

	tcgetattr(1, &term_settings);
	term_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &term_settings);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	atexit(check_leaks);
	using_history();
	signals();
	if (argument_protection(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	debug_print_t_expander(data.expander);
	signals();
	while (g_signal >= 1)
	{
		if (history(&data) == ERROR && g_signal != 2)
			break ;
		if (parser(&data) == ERROR)
			break ;
		if (executor(&data) == ERROR)
			break ;
		free_loop(&data);
	}
	free_env(&data);
	return (EXECUTED);
}

// @note error handling!
