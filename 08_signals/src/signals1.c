/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:48:02 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/28 16:01:44 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>

void	here_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(sig);
	}
}

