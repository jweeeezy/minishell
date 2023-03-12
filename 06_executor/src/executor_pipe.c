/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:35:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/12 20:42:49 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// needed for t_execute
#include <unistd.h>	// needed for fork(), NULL
#include <stdio.h>	// needed for perror()
#include "libft.h"	// needed for ft_split


