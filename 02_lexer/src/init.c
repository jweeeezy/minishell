/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:29:23 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/15 17:16:35 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

void	init_combine(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		data->combine[cnt].count_n = cnt;
		data->combine[cnt].combined_str = NULL;
		data->combine[cnt].full_path = NULL;
		cnt++;
	}
}
