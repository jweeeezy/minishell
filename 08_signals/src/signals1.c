/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:48:02 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 21:46:41 by jwillert         ###   ########.fr       */
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
#include "redirector.h"

void	here_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(sig);
	}
}
