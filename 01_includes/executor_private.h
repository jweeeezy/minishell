/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/25 21:09:46 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PRIVATE_H
# define EXECUTOR_PRIVATE_H

# include "minishell.h"

int		executor_main(t_data *data);
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

//		IS_UTILS
int		executor_is_redirection(t_combine cmd);
int		executor_is_heredoc(t_combine cmd);
int		executor_is_pipe(t_combine cmd);

//		COUNT_UTILS
int		executor_count_pipes(t_data *data);

#endif	// EXECUTOR_PRIVATE_H
