/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 18:12:48 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//			MAIN
int			executor(t_data *data);

//			PIPEX
int			executor_pipex(t_data *data);
int			pipex_skip_non_commands(t_data *data, int index);
int			pipex_advance_to_next_pipe(t_data *data, int index);

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
int			executor_parent(t_data *data, int index);

//			UTILS_count
int			executor_count_pipes(t_data *data);
int			executor_count_commands(t_data *data);
int			executor_count_redirections(t_data *data);
int			executor_count_heredocs(t_data *data);

//			CMD SELECTOR UTILS
int			selector_is_cmd_path_valid(t_combine *cmd);
int			selector_is_cmd_valid(t_combine *cmd, char **envp);

//			UTILS_is
int			executor_is_pipe(t_combine *cmd);
int			executor_is_redirection(t_combine *cmd);
int			executor_is_heredoc(t_combine *cmd);

#endif	// EXECUTOR_PRIVATE_H
