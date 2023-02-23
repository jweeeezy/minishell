/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/23 16:14:43 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	put_to_linked_list(t_data *data)
{
	t_line	*current_node;
	t_line	*new_node;
	int		i;

	current_node = NULL;
	i = 0;
	while (data->args[i] != NULL)
	{
		new_node = malloc(sizeof(t_line));
		new_node->str = data->args[i];
		new_node->next = NULL;
		if (data->lines == NULL)
		{
			data->lines = new_node;
			current_node = data->lines;
		}
		else
		{
			current_node->next = new_node;
			current_node = current_node->next;
		}
		i++;
	}
	return (0);
}

int	parsing(t_data *data)
{
	int	cnt;

	cnt = 0;
	data->args = tokenizer(data, 0, 0, 0);
	if (put_to_linked_list(data) == 1)
		return (1);
	return (0);
}
