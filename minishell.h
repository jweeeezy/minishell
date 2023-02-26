/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/26 10:40:01 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

enum e_outputs
{
	Error = -1,
	Executed = 0,
	Apostrophe = 3,
	Quotation_mark = 4,
	Pipe = 5,
	Dolla = 6,
	Shell_redirection = 17,
	Here_doc = 18,
	Command_to_file = 7,
	File_to_command = 8
};

typedef struct execute
{
	char			*order_str;
	int				order_numb;
	struct execute	*next;
}	t_execute;

typedef struct expander
{
	char			*str;
	struct expander	*next;
}	t_expander;

typedef struct data
{
	char			**args;
	int				tokens;
	t_execute		*execute;
	char			*line;
	char			*prompt;
	char			**envp;
	char			**argv;
	t_expander		*expander;
}	t_data;

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
