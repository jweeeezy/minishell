/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/10 13:51:22 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
		free(data->execute[cnt].order_str);
		free(data->execute[cnt].full_path);
		cnt++;
	}
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
		if (DEBUG)
			printf("Freeing... [%s]\n", array_to_free[index]);
		free (array_to_free[index]);
		index += 1;
	}
	free (array_to_free);
}
