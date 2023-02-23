/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/23 16:18:26 by kvebers          ###   ########.fr       */
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
	t_line	*current_node;
	t_line	*next_node;

	current_node = data->lines;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	data->lines = NULL;
}

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	free_lines(data);
	free(data->args);
}
