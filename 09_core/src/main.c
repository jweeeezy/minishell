/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/22 13:20:57 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <unistd.h>

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

void	check_leaks(void)
{
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

	if (DEBUG)
		atexit(check_leaks);
	using_history();
	if (argument_protection(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	debug_print_t_expander(data.expander);
	while (1)
	{
		if (history(&data) == ERROR)
			break ;
		if (parser(&data) != ERROR)
			executor_main(&data);
		free_loop(&data);
	}
	free_env(&data);
	return (EXECUTED);
}
