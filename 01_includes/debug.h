/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:20:48 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 21:22:40 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# ifndef DEBUG
#  define DEBUG 0
# endif  // DEBUG

# include "minishell.h"

void	debug_print_pid(char *process_name);
void	debug_print_char_array(char **args, char *name);
void	debug_print_int(char *description, int int_to_print);
void	debug_print_t_execute(t_data *data,	t_execute *execute);
void	debug_print_t_combine(t_data *data);
void	debug_print_pipe_status(t_data *data, char *message, int **fd_pipes);
void	debug_print_fds(int max);
void	debug_print_redirections(t_data *data);
void	debug_print_t_heredoc(t_data *data);
void	debug_print_stage(char *stage, int level);
void	debug_stepper(char *message);

#endif	// DEBUG_H
