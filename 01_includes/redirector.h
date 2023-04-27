/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/27 12:52:21 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10

//		HEREDOC_LST_UPDATE
t_heredoc	*heredoc_lst_update(t_data *data);

//		HEREDOC LST UTILS
void		heredoc_lst_clean(t_data *data);
t_heredoc	*heredoc_lst_get_new_node(void);
t_heredoc	*heredoc_lst_get_by_index(t_heredoc *lst_to_loop, int index);
t_heredoc	*heredoc_lst_get_and_add_last(t_heredoc *lst_to_expand,
				t_heredoc *node_to_add);

//		HEREDOC

//		REDIRECTIONS
//int			redirector_handle_redirections(t_data *data);

//		REDIRECTION UTILS
int			redirector_find_end_of_command(t_data *data, int index);
char		*redirector_get_filename(t_data *data, int index, int token_type);
void		handle_open_error(t_data *data, char *str_filename, int flag_indirection);

#endif // REDIRECTOR_H
