/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 13:21:48 by kvebers          ###   ########.fr       */
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
		if (*data->line == '\0')
			return (EXECUTED);
		add_history(data->line);
		if (lexer(data) == ERROR)
			return (free(data->line), ERROR);
	}
	return (EXECUTED);
}

static void	check_leaks(void)
{
	if (DEBUG)
	{
		system ("leaks minishell");
	}
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
	signals();
	while (g_signal >= 1)
	{
		if (history(&data) == ERROR && g_signal != 2)
			break ;
		// if (parser(&data) != ERROR)
		// {
		// 	if (executor(&data) == ERROR)
		// 	{
		// 		if (DEBUG)
		// 			printf("Execution error\n");
		// 	}
		// }
		free_loop(&data);
	}
	return (EXECUTED);
}

// @note error handling!
