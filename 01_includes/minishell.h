/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:16:43 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/29 10:39:13 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>

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
	WIERD_N = 29,
	BUFFER_SIZE = 42,
	LAST_PIPE = 50,
	BUILTIN = 200,
	EXTERN = 100,
	NO_EXECUTION = -100
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
	int		order_numb;
	int		number;
}	t_execute;

typedef struct s_combine
{
	t_execute	*command;
	char		*combined_str;
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
	t_combine		*combine;
	t_heredoc		*heredoc;
	char			**envp;
	char			**argv;
	char			*line;
	int				exit_status;
	int				*child_pids;
	int				commands_to_process;
	int				counter_pipes;
	int				counter_processes;
	int				counter_commands;
	int				index_processes;
	int				tokens;
	int				flag_printed;
	int				flag_builtin_only;
	int				flag_heredoc;
	int				flag_infile;
	int				flag_outfile;
	int				fd_infile;
	int				fd_outfile;
	int				fd_stdin;
	int				fd_stdout;
	int				not_executed;
	pid_t			pid;
}	t_data;

/* ************************************************************************** */
//                                     CORE
/* ************************************************************************** */

int		init_data(t_data *data);
void	free_char_array(char **array_to_free);
void	free_loop(t_data *data);
int		argument_protection(t_data *data, int argc, char **argv, char **envp);
void	free_pipe_array(int **array, int size);
void	free_t_heredoc(t_data *data);
void	free_env(t_data *data);

/* ************************************************************************** */
//                                    UTILS
/* ************************************************************************** */

char	*ft_strjoin2(char *temp, char *buffer, size_t cnt1, size_t cnt2);
int		is_white_space(char c);
int		ft_strnstr2(const char *haystack, const char *needle, size_t t);
int		dolla_handler(t_data *data, int cnt, int cnt1);
int		count_split(char **split);
void	split_free(char **split);
int		q_state(char *str, int cnt, int quote_state);
char	*ft_strnstr3(const char *haystack, const char *needle, size_t length);
char	*ft_charjoin(char *temp, char c, size_t cnt1, size_t cnt2);
int		only_whites(char *str);
int		is_command_mixed(char *str, char *token);
int		is_command(char *str, char *token);
int		count_env(t_data *data);
int		is_n(char *str);

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
int		remove_edge_case1(t_data *data, int cnt, int cnt1);
int		check_parsing(t_data *data);
int		check_pies(t_data *data, int q);

/* ************************************************************************** */
//                                    PARSER
/* ************************************************************************** */

int		parser(t_data *data);
void	main_command(t_data *data);
int		recombine_str(t_data *data, int cnt, int cnt1, char *temp);
int		token_numbers_helper(char *str);
int		is_wierd_n(char *str);
void	fix_env_flags(t_data *data);
int		recheck_command(t_data *data);

/* ************************************************************************** */
//                                    REDIRECTOR
/* ************************************************************************** */

int		redirector_prehandle_heredocs(t_data *data);
int		redirector_handle_redirections(t_data *data, int index);
void	quote_main_command(t_data *data);

/* ************************************************************************** */
//                                    EXECUTOR
/* ************************************************************************** */

int		executor(t_data *data);

/* ************************************************************************** */
//                                    BUILTINS
/* ************************************************************************** */

void	echo(t_combine str, int n, int cnt2, int is_echo_skiped);
void	wierd_echo(t_combine str, int n, int cnt2, int is_echo_skiped);
int		is_builtin(int cmd_to_check);
int		builtin_pwd(void);
void	env(t_data *data);
void	builtin_exit(t_data *data, int exit_code, int index);
void	unset(t_data *data, int index);
void	builtin_export(t_data *data, int index);
void	unset_free(t_data *data, int len);
int		error_managment_env(t_data *data, char *str, int numb);
int		export_flag_managment(t_data *data, char *str, int numb);
int		builtin_cd(t_data *data, int index);

/* ************************************************************************** */
//                                    SIGNALS
/* ************************************************************************** */

void	handle_signal(int sig);
void	signals(void);
void	child_handler(int sig);
void	child_signals(void);
void	here_signals(int sig);
void	heredoc_signals(void);

/* ************************************************************************** */
//                                    EXPANDER
/* ************************************************************************** */

int		expand_line(t_data *data, int cnt, int q);
char	**tokenizer(char *str, int cnt, int char_counter, int temp_char);
char	*search_needle(t_data *data, char *needle);
char	*expand_tokens_helper(t_data *data, char *temp, int q, char **tokens);
int		action_calculation(int q, char **tokens, int cnt1);

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
void	debug_print_t_combine(t_data *data);
void	debug_print_pipe_status(char *message, int **fd_pipes);
void	debug_print_fds(int max);
void	debug_print_redirections(t_data *data);
void	debug_print_t_heredoc(t_data *data);
void	debug_print_stage(char *stage, int level);

#endif  // MINISHELL_H
