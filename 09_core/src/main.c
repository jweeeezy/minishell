/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/10 13:38:25 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include "libft.h"

static int	history(t_data *data)
{
	data->line = readline("Terminal Troublemakers: ");
	if (data->line == NULL)
		return (ERROR);
	else if (data->line)
	{
		add_history(data->line);
		if (lexer(data) == ERROR)
			return (free(data->line), ERROR);
		if (executor_main(data) == ERROR)
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
	if (DEBUG)
		debug_print_t_expander(data.expander);
	while (1)
	{
		if (history(&data) == ERROR)
			break ;
		if (parser(&data) == ERROR)
			break ;
		free_loop(&data);
	}
	return (EXECUTED);
}
