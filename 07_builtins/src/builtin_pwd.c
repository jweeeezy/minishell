/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:10:01 by jwillert          #+#    #+#             */
/*   Updated: 2023/02/24 16:24:57 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	builtin_pwd(void)
{
	char	*current_working_dir;

	current_working_dir = getcwd(NULL, 0);
	if (current_working_dir == NULL)
		return (-1);							//	@todo handle error
	printf("%s\n", current_working_dir);
	free(current_working_dir);
	return (0);
}
