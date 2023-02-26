/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 10:45:17 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calculate_command(t_data *data, int cnt)
{
	if (*(data->args[cnt]) == 39)
		return (Apostrophe);
	if (*(data->args[cnt]) == 34)
		return (Quotation_mark);
	if (*(data->args[cnt]) == '|')
		return (Pipe);
	if (*data->args[cnt] == '$')
		return (Dolla);
	if (data->args[cnt + 1] != NULL && *data->args[cnt] == '>'
		&& *(data->args[cnt + 1]) == '>')
		return (Shell_redirection);
	if (data->args[cnt + 1] != NULL && *data->args[cnt] == '<'
		&& *(data->args[cnt + 1]) == '<' && data->args[cnt + 1] != NULL)
		return (Here_doc);
	if (*data->args[cnt] == '>')
		return (Command_to_file);
	if (*data->args[cnt] == '<')
		return (File_to_command);
	if (*data->args[cnt] == '=')
		return (8);
	if (*data->args[cnt] == '\0')
		return (Executed);
	return (Executed);
}

int	command_line(t_data *data)
{
	int			cnt;
	t_execute	*command;

	command = malloc(sizeof(t_execute));
	if (command == NULL)
		return (Error);
	cnt = 0;
	while (data->args[cnt] != NULL)
	{
		command->order_numb = calculate_command(data, cnt);
		printf("%i\n", command->order_numb);
		cnt++;
	}
	return (Executed);
}

int	parsing(t_data *data)
{
	int	cnt;

	cnt = 0;
	data->args = tokenizer(data, 0, 0, 0);
	command_line(data);
	return (Executed);
}
