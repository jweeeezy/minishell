/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/25 11:42:05 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct Execute
{
	char			*order_str;
	int				order_numb;
	struct Execute	*execute;
}	t_execute;

typedef struct Line
{
	char		*str;
	struct Line	*next;
}	t_line;

typedef struct Expander
{
	char			*str;
	struct Expander	*next;
}	t_expander;

typedef struct data
{
	char		**args;
	int			tokens;
	t_line		*lines;
	char		*line;
	char		*promt;
	char		**envp;
	char		**argv;
	t_expander	*expander;
}	t_data;

//	@todo Research enums and add Macros/enums for Error codes

//free.c
void	free_after_break(t_data *data);
char	**free_tokens(char **tokens);
void	free_loop(t_data *data);
int		parsing(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);
//parser
//tokenizer.c
char	**tokenizer(t_data *data, int cnt, int char_counter, int temp_char);
//env_to_list.c
int	put_to_linked_list_expander(t_data *data, char **envp);
#endif
