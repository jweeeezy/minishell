/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 15:51:23 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (lexer(data) == 1)
			return (free(data->line), ERROR);
	}
	return (EXECUTED);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	using_history();
	if (argument_protection(&data, argc, argv, envp) == 1)
		return (ERROR);
	if (init_data(&data) == 1)
		return (ERROR);
	while (1)
	{
		if (history(&data) == 1)
			break ;
		free_loop(&data);
	}
	free_after_break(&data);
	return (EXECUTED);
}
