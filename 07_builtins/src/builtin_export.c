/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:25:33 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 15:46:39 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static int	export_helper2(t_data *data, int len, char *str, char **tokens)
{
	char	**new_envp;
	int		cnt;

	cnt = 0;
	new_envp = NULL;
	if (ft_strchr(tokens[0], ' ') != NULL)
		return (ERROR);
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (new_envp == NULL)
		return (ERROR);
	while (cnt < len)
	{
		new_envp[cnt] = NULL;
		new_envp[cnt] = ft_strdup(data->envp[cnt]);
		cnt++;
	}
	new_envp[cnt] = ft_strdup(str);
	new_envp[cnt + 1] = NULL;
	unset_free(data, len);
	data->envp = new_envp;
	return (EXECUTED);
}

static int	export_helper1(t_data *data, int len, char *str, char **tokens)
{
	int		cnt1;
	char	*temp;

	cnt1 = 0;
	temp = NULL;
	temp = ft_strjoin(tokens[0], "=");
	while (cnt1 < len)
	{
		if (ft_strnstr3(data->envp[cnt1], temp, ft_strlen(temp)) != NULL)
		{
			free(data->envp[cnt1]);
			data->envp[cnt1] = NULL;
			data->envp[cnt1] = ft_strdup(str);
			if (data->envp[cnt1] == NULL)
				return (free(temp), ERROR);
			break ;
		}
		cnt1++;
	}
	if (cnt1 == len)
		export_helper2(data, len, str, tokens);
	if (temp != NULL)
		free(temp);
	return (EXECUTED);
}

static int	export_helper(t_data *data, int index, int len, int cnt)
{
	char	**tokens;

	if (ft_strchr(data->combine[index].execute[cnt].order_str, '=') != NULL)
	{
		tokens = ft_split(data->combine[index].execute[cnt].order_str, '=');
		if (tokens == NULL)
			return (ERROR);
		if (tokens[0] == NULL || export_helper1(data, len,
				data->combine[index].execute[cnt].order_str, tokens) == ERROR)
		{
			ft_putstr_fd("ERROR\n", 2);
			data->exit_status = 1;
			split_free(tokens);
			return (ERROR);
		}
		split_free(tokens);
	}
	else
		return (EXECUTED);
	return (EXECUTED);
}

void	builtin_export(t_data *data, int index)
{
	int		cnt;
	int		len;

	cnt = 0;
	if (ft_strncmp(data->combine[index].execute[cnt].order_str,
			"export",
			ft_strlen(data->combine[index].execute[cnt].order_str)) != 0)
		cnt++;
	while (cnt < data->combine[index].count_n)
	{
		len = count_env(data);
		export_helper(data, index, len, cnt);
		cnt++;
	}
}
