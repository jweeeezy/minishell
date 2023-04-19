/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:38:29 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/19 14:38:35 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"   

int	is_n(char *str)
{
	if (ft_strncmp(str, "-n", ft_strlen(str)) == 0)
		return (ADD);
	return (EXECUTED);
}
