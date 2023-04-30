/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 20:10:11 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ************************************************************************** */
//								CD_UTILS
/* ************************************************************************** */

int		find_var_index(char **envp, char *var_name);
char	*get_var_content(char **envp, char *var_name);
char	*get_destination(t_data *data, char **input, char *temp,
			int *flag_allocation);

#endif //	BUILTINS_H
