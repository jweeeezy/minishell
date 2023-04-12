/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/12 16:55:10 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10


//		HEREDOC UTILS
int			heredoc_check_duplicate_hash(t_heredoc *head, t_heredoc *node_to_compare);
int			heredoc_create_hash(char *string_to_hash);
int			heredoc_create_file(t_heredoc *node_to_edit);
char		*heredoc_get_delimiter(t_data *data, int index);

//		HEREDOC LST UTILS
t_heredoc	*heredoc_lst_get_new_node(void);
t_heredoc	*heredoc_lst_get_and_add_last(t_heredoc *lst_to_expand,
				t_heredoc *node_to_add);
t_heredoc	*heredoc_lst_get_by_index(t_heredoc *lst_to_loop, int index);
t_heredoc	*heredoc_lst_get_and_update_lst(t_data *data);
void		heredoc_lst_clean(t_data *data);

//		MAIN

//		REDIRECTIONS
int			redirector_prehandle_redirections(t_data *data, int counter_redirections);
void		redirector_handler_output(t_data *data);
void		redirector_handler_input(t_data *data);
static int	redirector_crossroads(t_data *data, int index, int flag_redirection);
static int	redirector_assign_heredoc(t_data *data);
static int	redirector_assign_infile(t_data *data, char *str_filename);
static int	redirector_assign_outfile_append(t_data *data, char *str_filename);
static int	redirector_assign_outfile(t_data *data, char *str_filename);

//		UTILS
int			redirector_find_end_of_command(t_data *data, int index);
char		*redirector_get_filename(t_data *data, int index);

# endif // REDIRECTOR_H
