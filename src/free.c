/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/21 18:07:48 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_after_break(t_data *data)
{
	free(data->promt);
	free(data);
}

void	free_lines(t_data *data)
{
	t_line *current;
	t_line *temp;
	
	current = data->lines;
	while (current != NULL) 
	{
    	temp = current;
    	current = current->next;
    	free(temp->data);
    	free(temp);
	}
}

void	free_loop(t_data *data)
{
	int cnt;

	cnt = 0;
	free_lines(data);
	while (data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
		cnt++;
	}
	free(data->args);
}
