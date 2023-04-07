/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/07 17:35:55 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10

//			UTILS	
void		heredoc_child_close_fd_before(t_data *data, t_heredoc *current_node);
void		heredoc_clean_lst(t_data *data, int flag_input);
t_heredoc	*heredoc_get_new_node(void);
t_heredoc	*heredoc_get_node_by_index(t_heredoc *lst_to_loop, int index);
t_heredoc	*heredoc_add_back(t_heredoc *lst_to_expand, t_heredoc *node_to_add);
int			heredoc_count_nodes(t_heredoc *lst_to_loop);
int			redirector_prehandle_heredocs(t_data *data, int counter_heredocs);
char		*redirector_get_filename(t_data *data, int index);
int			redirector_find_end_of_command(t_data *data, int index);

//			HEREDOC
int			heredoc_create_pipe(t_heredoc *node_to_edit);
char		*heredoc_get_delimiter(t_data *data, int index);
t_heredoc	*heredoc_create_lst(t_data *data);
int			heredoc_open_heredoc(t_data *data, int index, t_heredoc *current_node);
int			redirector_open_heredocs(t_data *data, int counter_heredocs);
int			redirector_prehandle_redirections(t_data *data, int index);

# endif // REDIRECTOR_H
