/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/24 11:02:20 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	quoter(t_data *data, int cnt, int q)
{
	char	*temp;

	temp = NULL;
	while (data->line[cnt] != '\0')
	{
		q = q_state(data->line, cnt, q);
		cnt++;
	}
	if (q > 0)
		return (ERROR);
	return (EXECUTED);
}

int	piper(t_data *data)
{
	size_t	cnt;

	cnt = 0;
	while (data->line[cnt] != '\0')
	{
		if (data->line[0] == '|')
			return (ERROR);
		if (cnt == ft_strlen(data->line) - 1)
		{
			if (data->line[cnt] == '|')
				return (ERROR);
		}
		if (cnt == ft_strlen(data->line) - 1)
		{
			if (data->line[cnt] == '<')
				return (ERROR);
		}
		if (cnt == ft_strlen(data->line) - 1)
		{
			if (data->line[cnt] == '>')
				return (ERROR);
		}
		cnt++;
	}
	return (EXECUTED);
}

int	check_the_sames(char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (str[cnt] != '\0')
	{
		if (is_white_space(str[cnt]) == 1
			|| str[cnt] == c)
			cnt++;
		else
			return (EXECUTED);
	}
	return (ERROR);
}

int	big_if(t_data *data)
{
	if (check_the_sames(data->line, '-') == ERROR
		|| (check_the_sames(data->line, '.') == ERROR)
		|| (check_the_sames(data->line, '\"') == ERROR)
		|| (check_the_sames(data->line, '\'') == ERROR)
		|| (check_the_sames(data->line, 92) == ERROR))
	{
		data->exit_status = 127;
		ft_putstr_fd("ERROR Symbols\n", 2);
		return (ERROR);
	}
	else if (check_the_sames(data->line, '/') == ERROR
		|| (check_the_sames(data->line, '~') == ERROR))
	{
		data->exit_status = 126;
		ft_putstr_fd("ERROR Symbols\n", 2);
		return (ERROR);
	}
	return (EXECUTED);
}

int	check_parsing(t_data *data)
{
	char	*temp;

	temp = NULL;
	if (quoter(data, 0, 0) == ERROR)
	{
		data->exit_status = 2;
		ft_putstr_fd("ERROR QUOTES\n", 1);
		return (ERROR);
	}
	if (piper(data) == ERROR)
	{
		data->exit_status = 2;
		ft_putstr_fd("ERROR Incorect PIPES\n", 2);
		return (ERROR);
	}
	if (big_if(data) == ERROR || check_wierd(data, data->line) == ERROR)
		return (ERROR);
	return (EXECUTED);
}
