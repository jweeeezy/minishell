/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/16 16:49:34 by jwillert         ###   ########.fr       */
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
#include "redirector.h"
#include "get_next_line_bonus.h"

#define INTERACTIVE 1
#define NON_INTERACTIVE 0

static int	history(t_data *data, int mode)
{
	if (mode == INTERACTIVE)
	{
		data->line = readline("Terminal Troublemakers: ");
	}
	else
	{
		data->line = get_next_line(STDIN_FILENO);
		printf("%s", data->line);
	}
	if (data->line == NULL)
		return (ERROR);
	else if (data->line)
	{
		if (*data->line == '\0')
			return (EXECUTED);
		if (mode == INTERACTIVE)
			add_history(data->line);
		if (data->line == NULL)
			return (EXECUTED);
		if (lexer(data) == ERROR)
			return (ERROR);
	}
	return (EXECUTED);
}

// static void	check_leaks(void)
// {
// 	if (DEBUG)
// 	{
// 		system ("leaks minishell");
// 	}
// }

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
	int		mode;

	if (isatty(fileno(stdin)))
	{
		mode = INTERACTIVE;
	}
	else
	{
		mode = NON_INTERACTIVE;
	}

	// atexit(check_leaks);
	if (mode == INTERACTIVE)
	{
		using_history();
	}
	if (argument_protection(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	signals();
	while (g_signal >= 1)
	{
		if (history(&data, mode) == ERROR && g_signal != 2)
			break ;
		if (parser(&data) != ERROR)
		{
			if (DEBUG)
			{
				debug_tokens(&data);
				debug_print_t_combine(&data);
			}
			if (redirector_prehandle_heredocs(&data) == ERROR)
			{
				printf("Redirection error\n");
			}
			// @note free heredoc lst / fd?
			if (executor(&data) == ERROR)
			{
				//printf("Execution error\n");
				free_t_heredoc(&data);
			}
		}
		free_loop(&data);
		if (mode == NON_INTERACTIVE)
			return (EXECUTED);
		//system("leaks minishell");
	}
	return (EXECUTED);
}
