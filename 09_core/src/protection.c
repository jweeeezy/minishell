/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:11:31 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/27 13:37:55 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	free_envp_error(t_data *data, int cnt1)
{
	int	cnt;

	cnt = 0;
	while (cnt < cnt1)
	{
		free(data->envp[cnt]);
		data->envp[cnt] = NULL;
		cnt++;
	}
	free(data->envp);
}

static int	set_defaults(t_data *data)
{
	char	*path;

	path = NULL;
	data->envp = malloc(sizeof(char *) * 4);
	if (data->envp == NULL)
		return (ERROR);
	data->envp[4] = NULL;
	data->envp[3] = NULL;
	data->envp[2] = NULL;
	data->envp[1] = NULL;
	data->envp[0] = NULL;
	path = getcwd(path, sizeof(path));
	data->envp[0] = ft_strjoin("PWD=", path);
	data->envp[1] = ft_strdup("SHLVL=1");
	data->envp[2] = ft_strdup("_=/usr/bin/env");
	return (free(path), EXECUTED);
}

static int	copy_envp_values(t_data *data, char **envp, int cnt, int cnt1)
{
	int	offset;

	offset = 0;
	while (cnt1 + offset < cnt)
	{
		data->envp[cnt1] = NULL;
		if (ft_strncmp(envp[cnt1 + offset], "OLDPWD=", 7) == 0)
		{
			offset += 1;
		}
		data->envp[cnt1] = ft_strdup(envp[cnt1 + offset]);
		if (data->envp[cnt1] == NULL)
		{
			free_envp_error(data, cnt1);
			return (ERROR);
		}
		cnt1++;
	}
	data->envp[cnt1] = NULL;
	return (EXECUTED);
}

static int	init_envp(t_data *data, char **envp, int cnt, int cnt1)
{
	int	offset;

	offset = 0;
	while (envp[cnt] != NULL)
		cnt++;
	if (cnt > 0)
		data->envp = malloc(sizeof(char *) * (cnt + 1));
	else
	{
		set_defaults(data);
		return (EXECUTED);
	}
	if (copy_envp_values(data, envp, cnt, cnt1) == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}

int	argument_protection(t_data *data, int argc, char **argv, char **envp)
{
	g_signal = 256;
	data->pid = getpid();
	if (argc > 1)
		return (ERROR);
	data->argv = argv;
	data->exit_status = 0;
	if (init_envp(data, envp, 0, 0) == ERROR)
		return (ERROR);
	data->heredoc = NULL;
	data->flag_infile = 0;
	data->flag_outfile = 0;
	data->flag_heredoc = 0;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->flag_builtin_only = 0;
	data->fd_stdin = dup(STDIN_FILENO);
	data->fd_stdout = dup(STDOUT_FILENO);
	return (EXECUTED);
}
