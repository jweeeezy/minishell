/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/29 14:08:47 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

void	last_pipe(t_data *data)
{
	int	cnt;

	cnt = data->commands_to_process - 1;
	while (cnt > -1)
	{
		if (data->combine[cnt].count_n > 0)
		{
			if (data->combine[cnt].execute[0].order_numb == PIPE)
			{
				data->combine[cnt].execute[0].order_numb = LAST_PIPE;
				return ;
			}
		}
		cnt--;
	}
}

int	token_numbers_helper(char *str)
{
	if (ft_strlen(str) >= 2 && str[0] == '<' && str[1] == '<'
		&& quoted_heredoc(str) == ADD)
		return (QUOTED_HEREDOC);
	else if (ft_strlen(str) >= 2 && str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if (ft_strlen(str) >= 2 && str[0] == '>' && str[1] == '>')
		return (SHELL_REDIRECTION);
	else if (ft_strlen(str) >= 1 && str[0] == '<')
		return (FILE_TO_COMMAND);
	else if (ft_strlen(str) >= 1 && str[0] == '>')
		return (COMMAND_TO_FILE);
	else if (ft_strlen(str) >= 1 && str[0] == '|')
		return (PIPE);
	return (0);
}

static int	token_numbers(char *str)
{
	if (is_command(str, "exit") == ADD)
		return (EXIT);
	else if (is_command(str, "export") == ADD)
		return (EXPORT);
	else if (is_command(str, "unset") == ADD)
		return (UNSET);
	else if (is_command(str, "echo") == ADD)
		return (ECHO);
	else if (is_command_mixed(str, "echo") == ADD)
		return (REJECTED_ECHO);
	else if (is_command_mixed(str, "env") == ADD)
		return (ENV);
	else if (is_command_mixed(str, "pwd") == ADD)
		return (PWD);
	else if (is_command(str, "cd") == ADD)
		return (CD);
	else if (is_n(str) == ADD)
		return (N);
	else if (is_wierd_n(str) == ADD)
		return (WIERD_N);
	return (STRING);
}

void	re_number(t_data *data)
{
	int	cnt;
	int	cnt1;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		cnt1 = 0;
		while (cnt1 < data->combine[cnt].count_n)
		{
			if (data->combine[cnt].execute[cnt1].order_numb == 0)
				data->combine[cnt].execute[cnt1].order_numb
					= token_numbers(data->combine[cnt].execute[cnt1].order_str);
			cnt1++;
		}
		cnt++;
	}
}

int	parser(t_data *data)
{
	if (data->line == NULL || *data->line == '\0')
		return (ERROR);
	debug_print_stage("parser", 0);
	re_number(data);
	last_pipe(data);
	main_command(data);
	fix_env_flags(data);
	if (recombine_str(data, 0, 0, NULL) == ERROR)
		return (ERROR);
	quote_main_command(data);
	return (EXECUTED);
}
