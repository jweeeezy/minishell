/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/28 20:21:06 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	echo_skip_white_spaces(char *str, int cnt1)
{
	if (*(str + cnt1) == ' '
		|| *(str + cnt1) == '\t'
		|| *(str + cnt1) == '\t'
		|| *(str + cnt1) == '\n'
		|| *(str + cnt1) == '\r'
		|| *(str + cnt1) == '\v'
		|| *(str + cnt1) == '\f')
		return (ADD);
	return (EXECUTED);
}

void	print_without_quotes(t_data	*data, int segment, int cnt)
{
	int	print;

	print = 1;
	cnt = ft_strnstr2(data->args[0], "echo", ft_strlen(data->args[0])) + 5;
	while (*(data->args[segment] + cnt) != '\0')
	{
		if (print == 0 && echo_skip_white_spaces(data->args[0], cnt) == ADD)
		{
			print = 1;
			ft_printf("%c", *(data->args[0] + cnt));
		}
		else if (print == 1
			&& echo_skip_white_spaces(data->args[0], cnt) == ADD)
		{
			cnt++;
			continue ;
		}
		else
		{
			ft_printf("%c", *(data->args[0] + cnt));
			print = 0;
		}
		cnt++;
	}
}

int	echo(t_data *data, int segment)
{
	print_without_quotes(data, segment,
		ft_strnstr2(data->args[segment], "echo", ft_strlen(data->args[0])) + 5);
	// while (utils_check_for_chars(data, segment) == EXECUTED)
	// {
	// 	if ()
	// 	segment++;
	// }
	ft_printf("%c", '\n');
	return (EXECUTED);
}
