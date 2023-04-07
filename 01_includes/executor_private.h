/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/07 14:56:00 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PRIVATE_H
# define EXECUTOR_PRIVATE_H

# include "minishell.h"

//			MAIN
int			executor(t_data *data);
// static int	executor_crossroads(t_data *data);
// static int	executor_init(t_data *data);
// static int	executor_wait_for_childs(t_data *data);

//			PIPEX
int			executor_pipex(t_data *data);
// static int	**pipex_create_pipes(int counter_pipes);
// static int	pipex_skip_non_commands(t_data *data, t_combine *cmd,
// 				int index);

//			CMD_SELECTOR
int			executor_cmd_selector(t_data *data, int **fd_pipes, int index);
// static int	selector_fork_and_execute(t_data *data, int **fd_pipes,
// 				int index, int flag_cmd);
// static int	selector_is_cmd_valid(t_execute *cmd, char **envp);
// static int	selector_try_access(t_execute *cmd, char *path, char *command);
// static char	**selector_get_path_array(char **envp);

//			CHILD
void		executor_child(t_data *data, int **fd_pipes, int index,
				int flag_cmd);
// static int	child_execute_builtin(t_data *data, int index);
// static int	child_execute_extern(t_data *data, int index);
// static void	child_prepare_pipes(int **fd_pipes, int index, 
// 				int counter_pipes);
// static void	child_close_pipes_after(int **fd_pipes, int start);
// static void	child_close_pipes_before(int **fd_pipes, int end);

//			CHILD_UTILS
void		child_prepare_pipes(int **fd_pipes, int index, int counter_pipes);

//			PARENT
int			executor_parent(t_data *data, int **fd_pipes, int index);

//			UTILS_count
int			executor_count_pipes(t_data *data);
int			executor_count_processes(t_data *data);
int			executor_count_redirections(t_data *data);
int			executor_count_heredocs(t_data *data);

//			UTILS_is
int			executor_is_pipe(t_combine *cmd);
int			executor_is_redirection(t_combine *cmd);
int			executor_is_heredoc(t_combine *cmd);
int			executor_is_cmd_path_valid(t_execute *cmd);

#endif	// EXECUTOR_PRIVATE_H
