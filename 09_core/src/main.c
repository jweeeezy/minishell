/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:47 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/05 13:33:10 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"

//	@note mb better sth like prompt_set or set_prompt and put in .h not in main
//	or we can do it on the stack so malloc is not needed.
int	init_data(t_data *data)
{
	data->prompt = ft_strdup("Terminal Troublemakers: ");
	if (data->prompt == NULL)
		return (ERROR);
	return (EXECUTED);
}

//	@note also prob better to put it in header if we want to use it again,
//	otherwise --> static
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
