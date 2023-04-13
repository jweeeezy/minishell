/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/13 19:10:49 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

int	is_command_mixed(char *str, char *token)
{
	char	*temp;
	int		cnt;

	cnt = 0;
	temp = NULL;
	while (str[cnt] != '\0')
	{
		temp = ft_charjoin(temp, ft_tolower(str[cnt]), 0, 0);
		if (temp == NULL)
			return (ERROR);
		cnt++;
	}
	if (ft_strlen(temp) == ft_strlen(token)
		&& ft_strnstr(temp, token, ft_strlen(temp)) != NULL)
		return (free(temp), ADD);
	return (free(temp), EXECUTED);
}

int	is_command(char *str, char *token)
{
	if (ft_strlen(str) == ft_strlen(token)
		&& ft_strnstr(str, token, ft_strlen(str)) != NULL)
		return (ADD);
	return (EXECUTED);
}

int	token_numbers(char *str)
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
		return (REJECTED_ECHO);
	else if (is_command_mixed(str, "pwd") == ADD)
		return (REJECTED_ECHO);
	else if (is_command(str, "cd") == ADD)
		return (REJECTED_ECHO);
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
		while (data->combine != NULL && cnt1 < data->combine[cnt].count_n)
		{
			if (cnt1 < data->combine[cnt].execute[cnt1].order_numb == 0)
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
	re_number(data);
	return (EXECUTED);
}
