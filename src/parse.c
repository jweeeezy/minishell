/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 11:34:40 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calculate_command(t_data *data, int cnt, int previous)
{
	if (*(data->args[cnt]) == 39)
		return (APOSTROPHE);
	if (*(data->args[cnt]) == 34)
		return (QUOTATION_MARK);
	if (*(data->args[cnt]) == '|')
		return (PIPE);
	if (*data->args[cnt] == '$')
		return (DOLLA);
	if (data->args[cnt + 1] != NULL && *data->args[cnt] == '>'
		&& *(data->args[cnt + 1]) == '>')
		return (SHELL_REDIRECTION);
	if (data->args[cnt + 1] != NULL && *data->args[cnt] == '<'
		&& *(data->args[cnt + 1]) == '<' && data->args[cnt + 1] != NULL)
		return (HERE_DOC);
	if (*data->args[cnt] == '>')
		return (COMMAND_TO_FILE + previous);
	if (*data->args[cnt] == '<')
		return (FILE_TO_COMMAND + previous);
	if (*data->args[cnt] == '=')
		return (EQUALS);
	if (*data->args[cnt] == '\0')
		return (EXECUTED);
	return (EXECUTED);
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
		command->order_numb = calculate_command(data, cnt, previous);
		if (command->order_numb == 18 || command->order_numb == 17)
			previous = command->order_numb;
		else
			previous = 0;
		printf("%i\n", command->order_numb);
		cnt++;
	}
	return (EXECUTED);
}

int	parsing(t_data *data)
{
	int	cnt;

	cnt = 0;
	data->args = tokenizer(data, 0, 0, 0);
	command_line(data);
	return (EXECUTED);
}
