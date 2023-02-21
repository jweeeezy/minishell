/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/21 13:49:42 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct Line
{
	char		*data;
	struct Line	*next;
}	t_line;

typedef struct data
{
	t_line	*lines;
	char	*line;
	char	*promt;
	char	**envp;
	char	**argv;
}	t_data;

//free.c
void	free_after_break(t_data *data);
void	free_loop(t_data *data);
int		parsing(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);

#endif
