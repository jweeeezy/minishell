/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:10:01 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/28 20:37:33 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>			// needed for getcwd(), NULL
#include <stdlib.h>			// needed for free()
#include <stdio.h>			// needed for printf()
#include "minishell.h"		// needed for MACRO

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
