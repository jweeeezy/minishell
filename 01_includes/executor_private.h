/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:22:50 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/14 10:29:35 by jwillert         ###   ########          */
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
t_execute	*get_string_after_pipe(t_execute *offset, t_execute *next_pipe);
//			@get_str_after_white might not be needed if parser handles that
t_execute	*get_string_after_whitespaces(t_execute *offset);

/* ************************************************************************** */
//								EXECUTOR_SETUP
/* ************************************************************************** */
int			try_access(t_execute *execute, char *path, char *command);
int			check_valid_command(t_execute *offset, char **envp);
//			@convert_command might not be needed if parser handles that
int			convert_command_to_vector(t_data *data, t_execute *offset);
char		**convert_vector_to_array(t_data *data);
