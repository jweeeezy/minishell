/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:11:46 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/25 07:46:50 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for free()
#include <stdio.h>			// needed for printf()
#include "minishell.h"		// needed for MACRO
#include "libft.h"

int	error_managment_env1(char *str)
{
	int	flag;

	flag = 0;
	if (ft_strlen(str) > 0 && str[0] == '-')
		flag = 2;
	else if (ft_strchr(str, '%') || ft_strchr(str, '@') || ft_strchr(str, '#')
		|| ft_strchr(str, '!') || ft_strchr(str, '=')
		|| ft_strchr(str, '.') || ft_strchr(str, '?') || ft_strchr(str, ' ')
		|| ft_strchr(str, '^') || ft_strchr(str, '~') || ft_strchr(str, '\\')
		|| ft_strchr(str, '-') || ft_strchr(str, '*') || ft_strchr(str, '{')
		|| ft_strchr(str, '}') || ft_strchr(str, '&'))
		flag = 1;
	else if (ft_strchr(str, ';'))
		flag = 127;
	else if (ft_strlen(str) > 0 && ft_strchr(str, '+') != NULL
		&& ft_strchr(str, '+') == (str + ft_strlen(str) - 1))
		flag = 0;
	else if (ft_strchr(str, '+'))
		flag = 1;
	return (flag);
}

int	error_managment_env(t_data *data, char *str, int numb)
{
	int	flag;

	flag = 0;
	if (numb == WHITE)
		return (EXECUTED);
	flag = error_managment_env1(str);
	if (flag > 0)
	{
		data->exit_status = flag;
		ft_putstr_fd("ERROR UNSET\n", 2);
	}
	return (flag);
}

int	export_flag_managment(t_data *data, char *str, int numb)
{
	char	**tokens;
	int		flag;

	tokens = NULL;
	flag = 0;
	if (numb == WHITE)
		return (EXECUTED);
	if (ft_strlen(str) > 0 && ft_strchr(str, '=') == NULL
		&& ft_isdigit(str[0]))
		flag = 1;
	else if (ft_strchr(str, '=') == NULL)
		return (EXECUTED);
	tokens = ft_split(str, '=');
	if (tokens == NULL || (ft_strlen(str) > 0 && (str[0] == '=')))
		flag = 1;
	else
		flag = error_managment_env1(tokens[0]);
	if (flag > 0)
	{
		data->exit_status = flag;
		ft_putstr_fd("EXPORT ERROR\n", 2);
	}
	split_free(tokens);
	return (flag);
}
