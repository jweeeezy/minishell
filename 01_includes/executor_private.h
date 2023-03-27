/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/27 10:12:25 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PRIVATE_H
# define EXECUTOR_PRIVATE_H

# include "minishell.h"

//		MAIN
int		executor_select_cmd(t_data *data, int **fd_pipes, int index);

//		PIPEX
int		executor_pipex(t_data *data);

//		BUILTIN
int		executor_builtin(t_data *data, int **fd_pipes, int index);

//		EXTERN
int		executor_extern(t_data *data, int **fd_pipes, int index);

//		EXTERN_child
void	executor_extern_child_routine(t_data *data, int **fd_pipes, int index);

//		EXTERN_parent
int		executor_extern_parent_routine(t_data *data, int **fd_pipes);

//		UTILS_IS
int		executor_is_redirection(t_combine *cmd);
int		executor_is_heredoc(t_combine *cmd);
int		executor_is_pipe(t_combine *cmd);

//		UTILS_COUNT
int		executor_count_pipes(t_data *data);
int		executor_count_heredocs(t_data *data);
int		executor_count_redirections(t_data *data);
int		executor_count_processes(t_data *data);

#endif	// EXECUTOR_PRIVATE_H
