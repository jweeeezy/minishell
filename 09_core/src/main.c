/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/28 13:54:32 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libme.h"
#include <readline/history.h>

int	init_data(t_data *data)
{
	data->prompt = ft_strdup("Terminal Troublemakers: ");
	if (data->prompt == NULL)
		return (ERROR);
	return (EXECUTED);
}

int	history(t_data *data)
{
	data->line = readline(data->prompt);
	if (data->line == NULL)
		return (ERROR);
	else if (data->line)
	{
		add_history(data->line);
		if (lexer(data) == ERROR)
			return (free(data->line), ERROR);
	}
	return (EXECUTED);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	using_history();
	if (argument_protection(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	if (init_data(&data) == ERROR)
		return (ERROR);
	while (1)
	{
		if (history(&data) == ERROR)
			break ;
		if (parser(&data) == ERROR)
			break ;
		free_loop(&data);
	}
	free_after_break(&data);
	return (EXECUTED);
}
