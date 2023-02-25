/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 13:03:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_data(t_data *data)
{
	data->promt = ft_strdup("Terminal Troublemakers: ");
	if (data->promt == NULL)
		return (1);
	return (0);
}

int	history(t_data *data)
{
	data->line = readline(data->promt);
	if (data->line == NULL)
		return (1);
	else if (data->line)
	{
		add_history(data->line);
		if (parsing(data) == 1)
			return (free(data->line), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
				//	@note we can prob put it on the stack instead of mallocing and pass the address, because child-processes cant share the same memory anyway
	using_history();
	if (argument_protection(&data, argc, argv, envp) == 1)
		return (1);
	if (init_data(&data) == 1)
		return (1);
	while (1)
	{
		if (history(&data) == 1)
			break ;
		free_loop(&data);
	}
	free_after_break(&data);
	return (0);
}
