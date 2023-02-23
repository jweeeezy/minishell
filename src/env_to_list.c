/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:47:50 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/23 18:32:33 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	put_to_linked_list_expander(t_data *data, char **envp)
{
	t_expander	*current_node;
	t_expander	*new_node;
	int			i;

	current_node = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = malloc(sizeof(t_expander));
		new_node->str = ft_strdup(envp[i]);
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
		i++;
	}
	return (0);
}
