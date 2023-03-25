/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/25 14:33:34 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

int	is_n(char *str)
{
	int	len;
	int	cnt;

	cnt = 0;
	len = ft_strlen(str);
	if (len > 1)
	{
		if (str[cnt] != '-')
			return (EXECUTED);
		cnt++;
		while (str[cnt] != '\0')
		{
			if (str[cnt] != 'n')
				return (EXECUTED);
			cnt++;
		}
		return (ADD);
	}
	return (EXECUTED);
}

static int	calculate_command_2(t_data *data, int cnt)
{
	if (*data->args[cnt] == '=')
		return (EQUALS);
	else if (is_n(data->args[cnt]) == ADD)
		return (N);
	else if (is_command(data, cnt, "echo") > 0)
		return (ECHO + is_command(data, cnt, "echo") - 1);
	else if (is_command1(data, cnt, "cd") > 0)
		return (CD + is_command1(data, cnt, "cd") - 1);
	else if (is_command(data, cnt, "pwd") > 0)
		return (PWD + is_command(data, cnt, "pwd") - 1);
	else if (is_command1(data, cnt, "unset") > 0)
		return (UNSET + is_command1(data, cnt, "unset") - 1);
	else if (is_command1(data, cnt, "export") > 0)
		return (EXPORT + is_command1(data, cnt, "export") - 1);
	else if (is_command1(data, cnt, "env") > 0)
		return (ENV + is_command1(data, cnt, "env") - 1);
	else if (is_command1(data, cnt, "exit") > 0)
		return (EXIT + is_command1(data, cnt, "exit") - 1);
	else if (is_white_space(*data->args[cnt]) == ADD)
		return (WHITE);
	else if (*data->args[cnt] == '\0')
		return (EXECUTED);
	return (STRING);
}

static int	calculate_command_1(t_data *data, int cnt, int previous)
{
	if (*(data->args[cnt]) == 39)
		return (APOSTROPHE);
	else if (*(data->args[cnt]) == 34)
		return (QUOTATION_MARK);
	else if (*(data->args[cnt]) == '|')
		return (PIPE);
	else if (*data->args[cnt] == '$')
		return (DOLLA);
	else if (data->args[cnt + 1] != NULL && *data->args[cnt] == '>'
		&& *(data->args[cnt + 1]) == '>')
		return (SHELL_REDIRECTION);
	else if (data->args[cnt + 1] != NULL && *data->args[cnt] == '<'
		&& *(data->args[cnt + 1]) == '<' && data->args[cnt + 1] != NULL)
		return (HERE_DOC);
	else if (*data->args[cnt] == '>' && previous == SHELL_REDIRECTION)
		return (COMMAND_TO_FILE + 10);
	else if (*data->args[cnt] == '<' && previous == HERE_DOC)
		return (FILE_TO_COMMAND + 10);
	else if (*data->args[cnt] == '>')
		return (COMMAND_TO_FILE);
	else if (*data->args[cnt] == '<')
		return (FILE_TO_COMMAND);
	else
		return (calculate_command_2(data, cnt));
}

static int	command_line(t_data *data)
{
	int	cnt;
	int	previous;

	data->execute = malloc(sizeof(t_execute) * data->tokens + 1);
	if (data->execute == NULL)
		return (ERROR);
	cnt = 0;
	previous = 0;
	while (data->args[cnt] != NULL)
	{
		data->execute[cnt].order_numb
			= calculate_command_1(data, cnt, previous);
		data->execute[cnt].order_str = ft_strdup(data->args[cnt]);
		data->execute[cnt].number = cnt;
		if (data->execute[cnt].order_numb == ERROR)
			return (ERROR);
		data->execute[cnt].full_path = NULL;
		previous = data->execute[cnt].order_numb;
		cnt++;
	}
	data->execute[cnt].order_str = NULL;
	return (EXECUTED);
}

int	lexer(t_data *data)
{
	data->tokens = 0;
	data->args = tokenizer(data, 0, 0, 0);
	if (command_line(data) == ERROR)
		return (ERROR);
	debug_print_char_array(data->args);
	debug_print_t_execute(data, data->execute);
	return (EXECUTED);
}
