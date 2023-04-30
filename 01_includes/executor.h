/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:07:43 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/* ************************************************************************** */
//                                EXECUTOR_CHILD
/* ************************************************************************** */
void		executor_child(t_data *data, int **fd_pipes, int index,
				int flag_cmd);
void		child_prepare_pipes(t_data *data, int **fd_pipes,
				int index, int counter_pipes);
int			child_execute_builtin(t_data *data, int index);

/* ************************************************************************** */
//                                CHILD_UTILS
/* ************************************************************************** */

void		child_close_pipes_before(int **fd_pipes, int end);
void		child_close_pipes_after(int **fd_pipes, int start);
void		child_handle_indirection(t_data *data);
void		child_handle_outdirection(t_data *data);
void		child_handle_pipes_and_redirections(t_data *data, int **fd_pipes);

/* ************************************************************************** */
//                                EXECUTOR_CMD_SELECTOR
/* ************************************************************************** */

int			executor_cmd_selector(t_data *data, int **fd_pipes, int index);

/* ************************************************************************** */
//                                SELECTOR_UTILS
/* ************************************************************************** */

void		selector_print_command_not_found(t_data *data);
int			selector_is_cmd_path_valid(t_combine *cmd);
int			selector_is_cmd_valid(t_combine *cmd, char **envp);

/* ************************************************************************** */
//                                EXECUTOR_PARENT
/* ************************************************************************** */

int			executor_parent(t_data *data, int index);
void		executor_parent_close_pipes(t_data *data, int **fd_pipes);

/* ************************************************************************** */
//                                EXECUTOR_PIPEX
/* ************************************************************************** */

int			executor_pipex(t_data *data);

/* ************************************************************************** */
//                                PIPEX_UTILS
/* ************************************************************************** */

int			pipex_skip_non_commands(t_data *data, int index);
int			pipex_advance_to_next_pipe(t_data *data, int index);

/* ************************************************************************** */
//                                 EXECUTOR_IS_UTILS
/* ************************************************************************** */

int			executor_is_pipe(t_combine *cmd);
int			executor_is_redirection(t_combine *cmd);
int			executor_is_heredoc(t_combine *cmd);
int			executor_is_t_combine_advanceable(t_data *data, int offset);

/* ************************************************************************** */
//                                 EXECUTOR_COUNT_UTILS
/* ************************************************************************** */

int			executor_count_pipes(t_data *data);
int			executor_count_commands(t_data *data);
int			executor_count_redirections(t_data *data);
int			executor_count_heredocs(t_data *data);

#endif	// EXECUTOR_PRIVATE_H
