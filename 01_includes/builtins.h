/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/04/30 17:30:46 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		find_var_index(char **envp, char *var_name);
char	*get_var_content(char **envp, char *var_name);
char	*get_destination(t_data *data, char **input, char *temp,
			int *flag_allocation);

#endif //	BUILTINS_H
