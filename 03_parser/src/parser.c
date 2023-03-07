/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:21:26 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/07 16:57:59 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_pipe(int c)
// {
// 	if (c == PIPE || c == SHELL_REDIRECTION || c == HERE_DOC
// 		|| c == FILE_TO_COMMAND || c == COMMAND_TO_FILE)
// 		return (ADD);
// 	return (EXECUTED);
// }

int	parser(t_data *data)
{
	int	cnt;
	// // int	main_command;

	cnt = 0;
	// // main_command = 100;
	 while (cnt < data->tokens)
	{
	// // 	if (is_pipe(data->execute[cnt].order_numb))
	// // 	{
	// // 		main_command = 100;
	// // 		cnt++;
	// // 		continue ;
	// // 	}
	// // 	else if (data->execute[cnt].order_numb != 2 && main_command == 100)
	// // 		main_command = data->execute[cnt].order_numb;
	// // 	data->ex
		cnt++;
	}
	return (EXECUTED);
}
