/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:47:50 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 13:06:50 by kvebers          ###   ########.fr       */
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

int	put_to_linked_list_expander(t_data *data, char **envp)
{
	t_expander	*current_node;
	t_expander	*new_node;
	int			i;

	current_node = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_new_expander_node(ft_strdup(envp[i]));
		if (new_node == NULL)
			return (1);
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
		i++;
	}
	return (0);
}