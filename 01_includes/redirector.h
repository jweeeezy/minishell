/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/07 15:50:27 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H


# define LAST -10

//			UTILS	
void		heredoc_child_close_fd(t_data *data, t_heredoc *current_node);
void		heredoc_clean_lst(t_data *data, int flag_input);
t_heredoc	*heredoc_get_new_node(void);
t_heredoc	*heredoc_get_node_by_index(t_heredoc *lst_to_loop, int index);
int			heredoc_add_back(t_heredoc *lst_to_expand, t_heredoc *node_to_add);
int			heredoc_count_nodes(t_heredoc *lst_to_loop);

//			HEREDOC
int			heredoc_create_pipe(t_heredoc *note_to_edit);
char		*heredoc_get_delimiter(t_data *data, int index);
t_heredoc	*heredoc_create_lst(t_data *data);
int			heredoc_open_heredoc(t_data *data, int index);
int			redirector_open_heredocs(t_data *data, int counter_heredocs);

# endif // REDIRECTOR_H
