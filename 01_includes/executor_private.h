/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/21 11:22:15 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PRIVATE_H
# define EXECUTOR_PRIVATE_H

# include "minishell.h"

/* ************************************************************************** */
//								EXECUTOR_UTILS
/* ************************************************************************** */
int			count_pipes(t_execute *execute);
char		**get_path_array(char **envp);
t_execute	*get_pipe(t_execute *offset);

/* ************************************************************************** */
//								EXECUTOR_SETUP
/* ************************************************************************** */
int			try_access(t_execute *execute, char *path, char *command);
int			check_valid_command(t_execute *offset, char **envp);
char		**convert_vector_to_array(t_data *data);

#endif	// EXECUTOR_PRIVATE_H
