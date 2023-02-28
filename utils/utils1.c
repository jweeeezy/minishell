/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:01:08 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/28 20:14:48 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	utils_check_for_chars(t_data *data, int segment)
{
	if (data->args[segment] || ft_strchr("<>|", data->args[segment]))
		return (ADD);
	return (EXECUTED);
}
