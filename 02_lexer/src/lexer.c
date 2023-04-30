/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:06 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/30 19:44:32 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_strdup()
#include <stdio.h>

int	merge_strings(t_data *data, int *numb1)
{
	int	cnt;
	int	cnt1;

	cnt1 = 0;
	cnt = 0;
	while (data->line[cnt] != '\0')
	{
		if (cnt1 == numb1[cnt])
		{
			data->combine[cnt1].combined_str
				= ft_charjoin(data->combine[cnt1].combined_str,
					data->line[cnt], 0, 0);
			if (data->combine[cnt1].combined_str == NULL)
				return (ERROR);
			cnt++;
		}
		else
			cnt1++;
	}
	return (EXECUTED);
}

int	create_strings(t_data *data, int *numb1)
{
	int	cnt;

	cnt = 0;
	while (data->line[cnt] != '\0')
		cnt++;
	if (cnt == 0)
		return (EXECUTED);
	data->commands_to_process = numb1[cnt - 1] + 1;
	data->combine = malloc(sizeof(t_combine) * (data->commands_to_process));
	if (data->combine == NULL)
		return (ERROR);
	init_combine(data);
	if (merge_strings(data, numb1) == ERROR)
		return (ERROR);
	return (EXECUTED);
}

int	command_line(t_data *data)
{
	int	*numb;
	int	*numb1;

	numb = NULL;
	numb1 = NULL;
	numb = malloc(sizeof(int) * ft_strlen(data->line));
	if (numb == NULL)
		return (ERROR);
	numb1 = malloc(sizeof(int) * ft_strlen(data->line));
	if (numb1 == NULL)
		return (free(numb), ERROR);
	determine_quote_state(data->line, 0, numb, numb1);
	if (create_strings(data, numb1) == ERROR)
		return (free(numb), free(numb1), ERROR);
	return (free(numb), free(numb1), EXECUTED);
}

int	lexer(t_data *data)
{
	char	*temp;

	temp = NULL;
	data->tokens = 0;
	data->not_executed = 0;
	data->commands_to_process = 0;
	if (data->line == NULL)
		return (ERROR);
	temp = ft_strtrim(data->line, " ");
	if (temp == NULL)
		return (ERROR);
	free(data->line);
	data->line = temp;
	if (check_parsing(data) == ERROR || command_line(data) == ERROR
		|| create_tokens(data) == ERROR)
	{
		data->not_executed = 1;
		return (EXECUTED);
	}
	return (EXECUTED);
}
