/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/14 14:27:02 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include "libme.h"	// needed for t_vector_str

int	g_signal;

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
	STRING = 10,
	SHELL_REDIRECTION = 17,
	HERE_DOC = 18,
	ECHO = 20,
	REJECTED_ECHO = 21,
	CD = 22,
	PWD = 23,
	EXPORT = 24,
	UNSET = 25,
	ENV = 26,
	EXIT = 27,
	N = 28,
	LAST_PIPE = 50,
	BUILTIN = 200,
	EXTERN = 100
};

typedef struct s_var
{
	int	cnt;
	int	cnt1;
	int	last;
}	t_var;

typedef struct s_execute
{
	char	*order_str;
	//char	*full_path;
	int		order_numb;
	int		number;
}	t_execute;

typedef struct s_combine
{
	t_execute	*command;
	char		*combined_str;
	char		*first_element;
	char		*full_path;
	int			count_n;
	t_execute	*execute;
}	t_combine;

typedef struct s_heredoc
{
	struct s_heredoc	*next;
	char				*full_path;
	unsigned long int	hash;
	int					fd;
}	t_heredoc;

typedef struct s_data
{
	//t_execute		*execute;
	t_combine		*combine;
	t_heredoc		*heredoc;
	char			**args;
	char			**envp;
	char			**argv;
	char			*line;
	int				*child_pids;
	int				commands_to_process;
	int				counter_pipes;
	int				counter_processes;
	int				index_processes;
	int				tokens;
	int				flag_heredoc;
	int				flag_infile;
	int				flag_outfile;
	int				fd_infile;
	int				fd_outfile;
}	t_data;

/* ************************************************************************** */
//                                     CORE
/* ************************************************************************** */

int		init_data(t_data *data);
void	free_char_array(char **array_to_free);
void	free_loop(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);
void	free_pipe_array(int **array, int size);

/* ************************************************************************** */
//                                    UTILS
/* ************************************************************************** */

char	*ft_strjoin2(char *temp, char *buffer, size_t cnt1, size_t cnt2);
int		is_white_space(char c);
int		ft_strnstr2(const char *haystack, const char *needle, size_t t);
//int		skip_white_spaces(t_data *data, int cnt);
int		dolla_handler(t_data *data, int cnt, int cnt1);
int		count_split(char **split);
void	split_free(char **split);
int		q_state(char *str, int cnt, int quote_state);
char	*ft_strnstr3(const char *haystack, const char *needle, size_t length);
char	*ft_charjoin(char *temp, char c, size_t cnt1, size_t cnt2);
int		only_whites(char *str);
int		is_command_mixed(char *str, char *token);
int		is_command(char *str, char *token);
/* ************************************************************************** */
//                                    LEXER
/* ************************************************************************** */

int		lexer(t_data *data);
void	determine_quote_state(char *str, int cnt, int *numb, int *numb1);
void	init_combine(t_data *data);
int		create_tokens(t_data *data);
void	init_tokens(t_data *data, int cnt1);
void	debug_tokens(t_data *data);
void	debug_print_combined(t_data *data);
int		remove_quotes(t_data *data, int cnt, int cnt1);
int		remove_null(t_data *data, int cnt);
int		remove_whitespaces(t_data *data, int cnt);
/* ************************************************************************** */
//                                    PARSER
/* ************************************************************************** */

int		parser(t_data *data);
void	main_command(t_data *data);
int		recombine_str(t_data *data, int cnt, int cnt1, char *temp);

/* ************************************************************************** */
//                                    REDIRECTOR
/* ************************************************************************** */

int		redirector_prehandle_heredocs(t_data *data);
int		redirector_handle_redirections(t_data *data);

/* ************************************************************************** */
//                                    EXECUTOR
/* ************************************************************************** */

int		executor(t_data *data);

/* ************************************************************************** */
//                                    BUILTINS
/* ************************************************************************** */

void	echo(t_combine str);
void	echo_n(t_data *data, int index);
int		is_builtin(int cmd_to_check);
char	builtin_pwd(void);
void	env(t_data *data);
/* ************************************************************************** */
//                                    SIGNALS
/* ************************************************************************** */

void	handle_signal(int sig);

/* ************************************************************************** */
//                                    EXPAND
/* ************************************************************************** */

int		expand_line(t_data *data, int cnt, int q);
char	**tokenizer(char *str, int cnt, int char_counter, int temp_char);
char	*search_needle(t_data *data, char *needle);

/* ************************************************************************** */
//                                    DEBUG
/* ************************************************************************** */

# ifndef DEBUG
#  define DEBUG 0
# endif  // DEBUG

void	debug_print_pid(char *process_name);
void	debug_print_char_array(char **args, char *name);
void	debug_print_int(char *description, int int_to_print);
void	debug_print_t_execute(t_data *data,	t_execute *execute);
void	debug_print_t_vector_str(t_vector_str *vector_to_print);
void	debug_print_t_combine(t_data *data);
void	debug_print_pipe_status(char *message, int **fd_pipes);
void	debug_fds(int max);

#endif  // MINISHELL_H
