/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:47:50 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 12:42:18 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_new_expander_node(char *str, t_expander *current_node, t_data *data)
{
	t_expander	*new_node;

	new_node = malloc(sizeof(t_expander));
	if (new_node == NULL)
		return (1);
	new_node->str = str;
    new_node->next = NULL;
	if (data->expander == NULL)
	{
		data->expander = new_node;
		current_node = data->expander;
	}
	else
	{
		current_node->next = new_node;
		current_node = current_node->next;
	}
	return (0);
}

int	put_to_linked_list_expander(t_data *data, char **envp)
{
	t_expander	*current_node;
	int			i;

	current_node = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (create_new_expander_node(ft_strdup(envp[i]),
				current_node, data) == -1)
			return (1);
		i++;
	}
	return (0);
}
