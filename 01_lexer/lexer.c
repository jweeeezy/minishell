/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 15:51:00 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_command(t_data *data, int cnt, char *needle)
{
	char	*upper_to_lower;
	int		cnt1;

	cnt1 = 0;
	upper_to_lower = ft_strdup(data->args[cnt]);
	if (upper_to_lower == NULL)
		return (ERROR);
	while (upper_to_lower[cnt1] != '\0')
	{
		upper_to_lower[cnt1] = ft_tolower(upper_to_lower[cnt1]);
		cnt1++;
	}
	cnt1 = ft_strnstr2(upper_to_lower, needle, ft_strlen(data->args[cnt]));
	if (cnt1 >= 0)
	{
		if (utils_is_command_helper(data, cnt1, cnt) > 1)
			return (free(upper_to_lower), EXECUTED);
		else if (utils_is_command_helper(data, cnt1, cnt) < 1
			&& utils_is_command_helper1(data, cnt1, cnt, needle) == 1)
			return (free(upper_to_lower), 1);
	}
	return (free(upper_to_lower), EXECUTED);
}

int	calculate_command_2(t_data *data, int cnt)
{
	if (*data->args[cnt] == '=')
		return (EQUALS);
	else if (is_command(data, cnt, "echo") > 0)
		return (ECHO + is_command(data, cnt, "echo") - 1);
	else if (is_command(data, cnt, "ls") > 0)
		return (LS + is_command(data, cnt, "ls") - 1);
	else if (is_command(data, cnt, "cd") > 0)
		return (CD + is_command(data, cnt, "cd") - 1);
	else if (*data->args[cnt] == '\0')
		return (EXECUTED);
	return (EXECUTED);
}

int	calculate_command_1(t_data *data, int cnt, int previous)
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

int	command_line(t_data *data)
{
	int			cnt;
	int			previous;
	t_execute	*command;

	command = malloc(sizeof(t_execute));
	if (command == NULL)
		return (ERROR);
	cnt = 0;
	previous = 0;
	while (data->args[cnt] != NULL)
	{
		command->order_numb = calculate_command_1(data, cnt, previous);
		previous = command->order_numb;
		printf("%i\n", command->order_numb);
		cnt++;
	}
	return (EXECUTED);
}

int	lexer(t_data *data)
{
	int	cnt;

	cnt = 0;
	data->args = tokenizer(data, 0, 0, 0);
	command_line(data);
	return (EXECUTED);
}
