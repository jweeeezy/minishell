/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/28 17:03:47 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <unistd.h>
#include <termios.h>
#include "redirector.h"
#include "get_next_line_bonus.h"

// static void	check_leaks(void)
// {
// 	return ;
// 	system("leaks minishell");
// }

static int	history(t_data *data)
{
	char	*line;

	data->flag_builtin_only = 0;
	data->flag_printed = 0;
	if (isatty(fileno(stdin)))
		data->line = readline("Terminal Troublemakers: ");
	else
	{
		line = get_next_line(fileno(stdin));
		data->line = ft_strtrim(line, "\n");
		free(line);
	}
	if (data->line == NULL)
		return (ERROR);
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

static void	extraordinary_error(t_data *data, char *message)
{
	if (data->flag_printed == 0)
	{
		ft_putstr_fd(message, 2);
		data->flag_printed = 1;
	}
}

static void	main_loop(t_data *data)
{
	while (g_signal >= 256)
	{
		signals();
		if (history(data) == ERROR || g_signal < 256)
			break ;
		if (parser(data) != ERROR && data->not_executed == 0)
		{
			data->exit_status = 0;
			if (redirector_prehandle_heredocs(data) == ERROR)
			{
				extraordinary_error(data, "HEREDOC ERROR\n");
			}
			if (executor(data) == ERROR)
			{
				extraordinary_error(data, "EXECUTION ERROR\n");
			}
		}
		free_loop(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	using_history();
	if (argument_protection(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	main_loop(&data);
	free_env(&data);
	exit(data.exit_status);
	return (EXECUTED);
}
