/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/21 18:11:13 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"










int	parsing(t_data *data)
{
    int cnt;

    cnt = 0;
    data->args = tokenizer(data, 0, 0, 0);
    while (data->args[cnt] != NULL)
    {
        printf("%s\n", data->args[cnt]);
        cnt++;
    }
    return (0);
}
