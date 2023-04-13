/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/13 14:15:58 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//			MAIN
int			executor(t_data *data);

//			PIPEX
int			executor_pipex(t_data *data);

//			CMD_SELECTOR
int			executor_cmd_selector(t_data *data, int **fd_pipes, int index);

//			CHILD
void		executor_child(t_data *data, int **fd_pipes, int index,
				int flag_cmd);

//			CHILD_UTILS
void		child_prepare_pipes(t_data *data, int **fd_pipes,
				int index, int counter_pipes);
void		child_handle_indirection(t_data *data);
void		child_handle_outdirection(t_data *data);

//			PARENT
int			executor_parent(t_data *data, int **fd_pipes, int index);

//			UTILS_count
int			executor_count_pipes(t_data *data);
int			executor_count_processes(t_data *data);
int			executor_count_redirections(t_data *data);
int			executor_count_heredocs(t_data *data);

//			CMD SELECTOR UTILS
int			selector_is_cmd_path_valid(t_combine *cmd);
int			selector_is_cmd_valid(t_combine *cmd, char **envp);

//			UTILS_is
int			executor_is_pipe(t_combine *cmd);
int			executor_is_redirection(t_combine *cmd);
int			executor_is_heredoc(t_combine *cmd);

int			pipex_skip_non_commands(t_data *data, t_combine *cmd, int index);

#endif	// EXECUTOR_PRIVATE_H
