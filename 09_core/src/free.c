/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/12 17:27:28 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->tokens && data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
		free(data->execute[cnt].order_str);
		free(data->execute[cnt].full_path);
		cnt++;
	}
	cnt = 0;
	while (cnt < data->commands_to_process
		&& data->combine[cnt].combined_str != NULL)
	{
		free(data->combine[cnt].combined_str);
		data->combine[cnt].combined_str = NULL;
		cnt++;
	}
	if (data->commands_to_process != 0)
		free(data->combine);
	free(data->execute);
	free(data->args);
	data->vector_args = NULL;
}

void	free_char_array(char **array_to_free)
{
	int	index;

	index = 0;
	while (array_to_free != NULL && array_to_free[index] != NULL)
	{
		free (array_to_free[index]);
		index += 1;
	}
	free (array_to_free);
}
