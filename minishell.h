/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/27 14:23:29 by kvebers          ###   ########.fr       */
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
	ERROR = -1,
	ADD = 1,
	EXECUTED = 0,
	APOSTROPHE = 3,
	QUOTATION_MARK = 4,
	PIPE = 5,
	DOLLA = 6,
	SHELL_REDIRECTION = 17,
	HERE_DOC = 18,
	COMMAND_TO_FILE = 7,
	FILE_TO_COMMAND = 8,
	EQUALS = 9,
	ECHO = 21,
	CD = 24,
	LS = 27,
	PWD = 31
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
int		lexer(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);
//parser
//tokenizer.c
char	**tokenizer(t_data *data, int cnt, int char_counter, int temp_char);
//env_to_list.c
int		put_to_linked_list_expander(t_data *data, char **envp);
//utils.c
int		ft_strnstr2(const char *haystack, const char *needle, size_t t);
int		utils_is_command_helper(t_data *data, int cnt1, int cnt);
int		utils_is_command_helper1(t_data *data, int cnt1, int cnt, char *needle);
int		is_command(t_data *data, int cnt, char *needle);
int		is_command1(t_data *data, int cnt, char *needle);
#endif
