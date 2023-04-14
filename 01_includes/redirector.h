/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/14 16:28:18 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10

t_heredoc	*heredoc_lst_update(t_data *data);

//		HEREDOC LST UTILS
void		heredoc_lst_clean(t_data *data);
t_heredoc	*heredoc_lst_get_new_node(void);
t_heredoc	*heredoc_lst_get_by_index(t_heredoc *lst_to_loop, int index);
t_heredoc	*heredoc_lst_get_and_add_last(t_heredoc *lst_to_expand,
				t_heredoc *node_to_add);

//		REDIRECTIONS
//int			redirector_handle_redirections(t_data *data);

//		UTILS
int			redirector_find_end_of_command(t_data *data, int index);
char		*redirector_get_filename(t_data *data, int index);

#endif // REDIRECTOR_H
