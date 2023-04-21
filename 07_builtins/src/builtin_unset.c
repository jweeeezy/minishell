/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:36:36 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/21 12:32:35 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for free()
#include <stdio.h>			// needed for printf()
#include "minishell.h"		// needed for MACRO
#include "libft.h"

void	unset_free(t_data *data, int len)
{
	int	cnt;

	cnt = 0;
	while (cnt < len)
	{
		if (data->envp[cnt] != NULL)
			free(data->envp[cnt]);
		cnt++;
	}
	free(data->envp);
}

int	count_env1(t_data *data, int cnt1, int cnt, int len)
{
	while (cnt < len)
	{
		if (data->envp[cnt] != NULL)
			cnt1++;
		cnt++;
	}
	return (cnt1);
}

int	recombabulate(t_data *data, int len)
{
	int		cnt;
	int		cnt1;
	char	**tokens;

	cnt = 0;
	cnt1 = count_env1(data, 0, 0, len);
	tokens = malloc(sizeof(char *) * (cnt1 + 1));
	if (tokens == NULL)
		return (ERROR);
	tokens[cnt1] = NULL;
	cnt = 0;
	cnt1 = 0;
	while (cnt < len)
	{
		tokens[cnt] = NULL;
		if (data->envp[cnt] != NULL)
		{
			tokens[cnt1] = ft_strdup(data->envp[cnt]);
			cnt1++;
		}
		cnt++;
	}
	unset_free(data, len);
	data->envp = tokens;
	return (EXECUTED);
}

void	unset_helper(t_data *data, int cnt, int len, int index)
{
	int		cnt1;
	char	*temp;

	cnt1 = 0;
	temp = ft_strjoin(data->combine[index].execute[cnt].order_str, "=");
	while (cnt1 < len)
	{
		if (data->envp[cnt1] == NULL)
		{
			cnt1++;
			continue ;
		}
		else if (ft_strnstr3(data->envp[cnt1], temp, ft_strlen(temp)) != NULL)
		{
			free(data->envp[cnt1]);
			data->envp[cnt1] = NULL;
		}
		cnt1++;
	}
	if (temp != NULL)
		free(temp);
}

void	unset(t_data *data, int index)
{
	int		cnt;
	int		len;
	int		error_msg;

	cnt = 0;
	error_msg = 0;
	len = count_env(data);
	if (ft_strncmp(data->combine[index].execute[cnt].order_str,
			"unset",
			ft_strlen(data->combine[index].execute[cnt].order_str)) != 0)
		cnt++;
	while (cnt < data->combine[index].count_n)
	{
		if (error_msg < 1)
			error_msg = error_managment_env(data, data->combine[index]
					.command[cnt].order_str, data->combine[index]
					.command[cnt].order_numb);
		if (error_msg == 0)
			unset_helper(data, cnt, len, index);
		cnt++;
	}
	recombabulate(data, len);
}
