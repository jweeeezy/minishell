/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:13:52 by kvebers           #+#    #+#             */
/*   Updated: 2022/11/01 19:07:49 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*ptr;	

	if (lst == NULL || del == NULL)
		return ;
	ptr = lst;
	(del)(lst -> content);
	lst = ptr -> next;
	free (ptr);
}
