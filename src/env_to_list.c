/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:47:50 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 15:36:45 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expander	*create_new_expander_node(char *str)
{
	t_expander	*new_node;

	new_node = malloc(sizeof(t_expander));
	if (new_node == NULL)
		return (NULL);
	new_node->str = str;
	new_node->next = NULL;
	return (new_node);
}

static int	t_expander_add_back(t_expander **lst_to_expand, t_expander *node_to_add)
{
	t_expander	*lst_index;

	lst_index = (*lst_to_expand);

	if (lst_to_expand == NULL || node_to_add == NULL)
		return (-1);
	while (lst_index->next != NULL)
		lst_index = lst_index->next;
	lst_index->next = node_to_add;
	return (0);
}

int	put_to_linked_list_expander(t_data *data, char **envp)
{
	t_expander	*current_node;
	size_t		index;

	current_node = data->expander;
	index = 0;
	while (envp[index] != NULL)
	{
		if (data->expander == NULL)
			data->expander = create_new_expander_node(ft_strdup(envp[index]));
		else
		{
			if (t_expander_add_back(&data->expander,
				create_new_expander_node(ft_strdup(envp[index]))) == -1)
				return (-1);
		}
		index++;
	}
	return (0);
}
