/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:47:50 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 14:27:29 by jwillert         ###   ########.fr       */
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

//	@note suggested code

int	put_to_linked_list_expander_new(t_data *data, char **envp)
{
	t_expander	*current_node;
	size_t		index;

	current_node = data->expander;
	index = 0;
	while (envp[index] != NULL)
	{
		if (data->expander == NULL)
			data->expander = create_new_expander_node(ft_strdup(envp[index]));
		else (t_expander_add_back(data->expander, create_new_expander_node(ft_strdup(envp[index]))) == -1)
			return (-1);
		index++;
	}
	return (0);
}

int	t_expander_add_back(t_expander *lst_to_expand, t_expander *node_to_add)
{
	if (lst_to_expand == NULL || node_to_add == NULL)
		return (-1);
	while (lst_to_expand->next != NULL)
		lst_to_expand = lst_to_expand->next;
	lst_to_expand->next = node_to_add;
}
