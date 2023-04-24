/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:58:09 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/24 12:50:31 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	check_wierd1(t_data *data, char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt + 1] == '\0')
			return (EXECUTED);
		if (str[cnt] == '<' || str[cnt] == '>' || str[cnt] == '|')
		{
			if (str[cnt + 1] == '<' || str[cnt + 1] == '>'
				|| str[cnt + 1] == '|')
			{
				if (str[cnt] != str[cnt + 1])
				{
					ft_putstr_fd("ERROR Wierd Pies and stuff", 2);
					data->exit_status = 127;
					return (ERROR);
				}
			}
		}
		cnt++;
	}
	return (EXECUTED);
}

int	check_wierd(t_data *data)
{
	char	*str;
	int		cnt;

	cnt = 0;
	str = NULL;
	while (data->line[cnt] != '\0')
	{
		if (is_white_space(data->line[cnt]) == 0)
			str = ft_charjoin(str, data->line[cnt], 0, 0);
		cnt++;
	}
	if (str != NULL)
		if (check_wierd1(data, str) == ERROR)
			return (free(str), ERROR);
	if (str != NULL)
		free(str);
	return (EXECUTED);
}

int	recheck_command(t_data *data)
{
	if (data->commands_to_process > 0 && data->combine[0].combined_str != NULL)
	{
		if ((is_white_space(data->combine[0].execute[0].order_str[0]) == ADD
				|| data->combine[0].execute[0].order_str[0] == '>'
				|| data->combine[0].execute[0].order_str[0] == '<'
				|| data->combine[0].execute[0].order_str[0] == '|'
				|| data->combine[0].execute[0].order_str[0] == '\0'
				|| data->combine[0].execute[0].order_str == NULL)
			&& (data->combine[0].execute[0].order_numb != PIPE
				|| data->combine[0].execute[0].order_numb != SHELL_REDIRECTION
				|| data->combine[0].execute[0].order_numb != HERE_DOC
				|| data->combine[0].execute[0].order_numb != FILE_TO_COMMAND
				|| data->combine[0].execute[0].order_numb != COMMAND_TO_FILE))
		{
			ft_putstr_fd("ERROR Wierd Pies and stuff", 2);
			data->exit_status = 127;
			return (ERROR);
		}
	}
	return (EXECUTED);
}
