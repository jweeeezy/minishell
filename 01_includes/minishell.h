/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/07 15:03:53 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>

enum e_outputs
{
	ERROR = -1,
	COMMAND_NOT_FOUND = -2,
	SYNTAX_ERROR = -3,
	PERMISSION_ERROR = -4,
	LOGIC_ERROR = -5,
	ENVIROMENTAL_ERROR = -6,
	PIPE_ERRORS = -7,
	VARIABLE_ERRORS = -8,
	EXECUTED = 0,
	ADD = 1,
	WHITE = 2,
	APOSTROPHE = 3,
	QUOTATION_MARK = 4,
	PIPE = 5,
	DOLLA = 6,
	COMMAND_TO_FILE = 7,
	FILE_TO_COMMAND = 8,
	EQUALS = 9,
	SHELL_REDIRECTION = 17,
	HERE_DOC = 18,
	ECHO = 20,
	CD = 21,
	LS = 22,
	PWD = 23,
	EXPORT = 24,
	UNSET = 25,
	ENV = 26,
	EXIT = 27
};

typedef struct s_echo
{
	int	double_quotes;
	int	single_quotes;
	int	redirections;
}	t_echo;

typedef struct s_execute
{
	char	*order_str;
	int		order_numb;
	char	*full_path;		// @note I need this for execution. On init = NULL
}	t_execute;

//	@note This is actually the list for the copied envp, right?
typedef struct s_expander
{
	char				*str;
	struct s_expander	*next;
}	t_expander;

typedef struct s_data
{
	char			**args;
	int				tokens;
	t_execute		*execute;
	char			*line;
	char			**envp;
	char			**argv;
	t_expander		*expander;
}	t_data;

/* ************************************************************************** */
//                                     CORE
/* ************************************************************************** */
int		init_data(t_data *data);
//char	**free_tokens(char **tokens);
void	free_loop(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);
int		ft_strnstr2(const char *haystack, const char *needle, size_t t);
int		utils_is_command_helper(t_data *data, int cnt1, int cnt);
int		utils_is_command_helper1(t_data *data, int cnt1, int cnt, char *needle);
int		is_command(t_data *data, int cnt, char *needle);
int		is_command1(t_data *data, int cnt, char *needle);
//int   utils_check_for_chars(t_data *data, int segment);
int		is_white_space(char c);

/* ************************************************************************** */
//                                    LEXER
/* ************************************************************************** */
int		lexer(t_data *data);
char	**tokenizer(t_data *data, int cnt, int char_counter, int temp_char);

/* ************************************************************************** */
//                                    PARSER
/* ************************************************************************** */
int		parser(t_data *data);
int		put_to_linked_list_expander(t_data *data, char **envp);

/* ************************************************************************** */
//                                    EXECUTOR
/* ************************************************************************** */
int		executor_main(t_data *data);

/* ************************************************************************** */
//                                    DEBUG
/* ************************************************************************** */
# ifndef DEBUG
#  define DEBUG 0
# endif  // DEBUG
void	debug_print_char_array(char **args);
void	debug_print_t_execute(t_data *data,
			t_execute *execute);
void	debug_print_t_expander(t_expander *expander);

#endif  // MINISHELL_H
