/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/25 12:46:29 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PRIVATE_H
# define EXECUTOR_PRIVATE_H

# include "minishell.h"

/* ************************************************************************** */
//								EXECUTOR_UTILS
/* ************************************************************************** */
int			count_pipes(t_data *data);
char		**get_path_array(char **envp);
t_execute	*get_pipe(t_execute *offset);

/* ************************************************************************** */
//								EXECUTOR_SETUP
/* ************************************************************************** */
int			try_access(t_execute *cmd, char *path, char *command);
int			check_valid_command(t_execute *cmd, char **envp);
char		**convert_str_to_array(t_combine *cmd);;

#endif	// EXECUTOR_PRIVATE_H
