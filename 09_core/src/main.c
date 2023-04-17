/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/18 00:18:53 by jwillert         ###   ########.fr       */
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

static void	check_leaks(void)
{
	return ;
	//system("leaks minishell");
}

static int	history(t_data *data)
{
	data->line = readline("Terminal Troublemakers: ");
	if (data->line == NULL)
	{
		return (ERROR);
	}
	else if (data->line)
	{
		if (*data->line == '\0')
			return (EXECUTED);
		add_history(data->line);
		if (data->line == NULL)
			return (EXECUTED);
		if (lexer(data) == ERROR)
			return (ERROR);
	}
	return (EXECUTED);
}

static int	non_interactive_mode(t_data *data)
{
	data->line = get_next_line(STDIN_FILENO);
	while (data->line != NULL)
	{
		if (lexer(data) == ERROR)
		{
			return (ERROR);
		}
		if (parser(data) != ERROR)
		{
			if (redirector_prehandle_heredocs(data) == ERROR)
			{
				printf("Redirection error\n");
			}
			if (executor(data) == ERROR)
			{
				printf("Execution error\n");
				free_t_heredoc(data);
			}
		}
		free_loop(data);
		free(data->line);
		data->line = get_next_line(STDIN_FILENO);
	}
	return (EXECUTED);
}

static int	interactive_mode(t_data *data)
{
	while (g_signal >= 1)
	{
		if (history(data) == ERROR && g_signal != 2)
		{
			break ;
		}
		if (parser(data) != ERROR)
		{
			if (redirector_prehandle_heredocs(data) == ERROR)
			{
				printf("Redirection error\n");
			}
			if (executor(data) == ERROR)
			{
				printf("Execution error\n");
				free_t_heredoc(data);
			}
		}
		free_loop(data);
	}
	return (EXECUTED);
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
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR1, ft_printer);
	signal(SIGUSR2, ft_printer);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	atexit(check_leaks);
	using_history();
	if (argument_protection(&data, argc, argv, envp) == ERROR)
	{
		return (ERROR);
	}
	signals();
	if (isatty(STDIN_FILENO))
	{
		if (interactive_mode(&data) == ERROR)
		{
			return (ERROR);
		}
	}
	else
	{
		if (non_interactive_mode(&data) == ERROR)
		{
			return (ERROR);
		}
	}
	exit(g_signal);
	return (EXECUTED);
}
