/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:10:01 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/21 12:11:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

char	builtin_pwd(void)
{
	char	*current_working_dir;

	current_working_dir = getcwd(NULL, 0);
	if (current_working_dir == NULL)
		return (ERROR);
	printf("%s\n", current_working_dir);
	free(current_working_dir);
	return (0);
}
