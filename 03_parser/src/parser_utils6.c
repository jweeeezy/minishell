/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:42:00 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/27 17:00:33 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft.h"

void	check_echo_n(t_data *data)
{
	int		cnt;
	size_t	cnt1;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		cnt1 = 4;
		if (data->combine[cnt].command->order_numb == ECHO)
		{
			while (is_white_space(*(data->combine[cnt].combined_str + cnt1))
				&& *(data->combine[cnt].combined_str + cnt1) != '\0')
				cnt1++;
			if (cnt1 + 1 < ft_strlen(data->combine[cnt].combined_str)
				&& *(data->combine[cnt].combined_str + cnt1) == '-'
				&& *(data->combine[cnt].combined_str + cnt1 + 1) == 'n')
				data->combine[cnt].command->order_numb = ECHO_N;
		}
		cnt++;
	}
}
