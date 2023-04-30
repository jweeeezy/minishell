/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:08:56 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10

t_heredoc	*heredoc_lst_update(t_data *data);
void		heredoc_child_routine(t_data *data, int index,
				t_heredoc *current_node, int status);

/* ************************************************************************** */
//							HEREDOC_LST_UTILS
/* ************************************************************************** */

void		heredoc_lst_clean(t_data *data);
t_heredoc	*heredoc_lst_get_new_node(void);
t_heredoc	*heredoc_lst_get_by_index(t_heredoc *lst_to_loop, int index);
t_heredoc	*heredoc_lst_get_and_add_last(t_heredoc *lst_to_expand,
				t_heredoc *node_to_add);

/* ************************************************************************** */
//							REDIRECTOR_UTILS
/* ************************************************************************** */

int			redirector_find_end_of_command(t_data *data, int index);
char		*redirector_get_filename(t_data *data, int index, int token_type);
void		handle_open_error(t_data *data, char *str_filename,
				int flag_indirection);

#endif // REDIRECTOR_H
