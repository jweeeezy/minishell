/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/26 13:02:55 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		find_var_index(char **envp, char *var_name);
char	*get_var_content(char **envp, char *var_name);
char	*get_destination(t_data *data, char **input, char *temp);

#endif //	BUILTINS_H
