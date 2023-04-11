/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:14 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/11 20:11:27 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_H
# define REDIRECTOR_H
# include "minishell.h"

# define LAST -10



//		HEREDOC UTILS
void	heredoc_clean_lst(t_data *data, int flag_input);
t_heredoc	*heredoc_get_new_node(void);
t_heredoc	*heredoc_add_back(t_heredoc *lst_to_expand, t_heredoc *node_to_add);
t_heredoc	*heredoc_get_node_by_index(t_heredoc *lst_to_loop, int index);
int	heredoc_count_nodes(t_heredoc *lst_to_loop);

//		HEREDOC_FILE
int	heredoc_check_duplicate_hash(t_heredoc *head, t_heredoc *node_to_compare);
int	heredoc_create_hash(char *string_to_hash);
int	heredoc_create_file(t_heredoc *node_to_edit);
char	*heredoc_get_delimiter(t_data *data, int index);
t_heredoc	*heredoc_create_lst(t_data *data);
int	heredoc_open_heredoc(t_data *data, int index, t_heredoc *current_node);
t_heredoc	*redirector_heredoc_update_lst(t_data *data);
int	redirector_prehandle_heredocs(t_data *data, int counter_heredocs);
int	redirector_fork_and_open_heredoc(t_data *data, int index,
		int counter_heredocs);


//		MAIN
int	redirector(t_data *data);

//		REDIRECTIONS
int	redirector_prehandle_redirections(t_data *data, int counter_redirections);
void	redirector_handler_output(t_data *data);
void	redirector_handler_input(t_data *data);
static int	redirector_crossroads(t_data *data, int index, int flag_redirection);
static int	redirector_assign_heredoc(t_data *data);
static int	redirector_assign_infile(t_data *data, char *str_filename);
static int	redirector_assign_outfile_append(t_data *data, char *str_filename);
static int	redirector_assign_outfile(t_data *data, char *str_filename);


//		UTILS
int	redirector_find_end_of_command(t_data *data, int index);
char	*redirector_get_filename(t_data *data, int index);


# endif // REDIRECTOR_H
