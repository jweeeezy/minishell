/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 13:08:12 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_line(t_data *data)
{
	int			cnt;
	t_execute	*new_node;

	new_node = malloc(sizeof(t_execute));
	if (new_node == NULL)
		return (1);
	cnt = 0;
	while (data->args[cnt] != NULL)
	{
		printf("%s\n", data->args[cnt]);
		cnt++;
	}
	return (0);
}

int	parsing(t_data *data)
{
	int	cnt;

	cnt = 0;
	data->args = tokenizer(data, 0, 0, 0);
	command_line(data);
	return (0);
}
