/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:08:01 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/30 13:20:22 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTOR_PRIVATE_H
# define REDIRECTOR_PRIVATE_H

# include "minishell.h"	// needed for t_data
						//
//		UTILS
char	*redirector_get_filename(t_data *data, int index);
int		redirector_find_offset_to_next_pipe(t_data *data, int index);

#endif	// REDIRECTOR_PRIVATE_H
