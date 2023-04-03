/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:41:33 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 23:00:36 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, ENUMS
#include "libft.h"      //  needed for ft_data->combine[cnt1].combined_strdup()
#include <stdio.h>

void	count_switcher(t_data *data, int *numb1, int cnt1)
{
	int	cnt;
	int	last_value;

	cnt = 0;
	last_value = -1;
	data->combine[cnt1].tks = 0;
	while (data->combine[cnt1].combined_str[cnt] != '\0')
	{
		if (last_value != numb1[cnt])
		{
			last_value = numb1[cnt];
			data->combine[cnt1].tks++;
		}
		cnt++;
	}
}

int	operations_with_blob(t_data *data, int *numb, int cnt1, int *numb1)
{
	int	cnt;
	int	switcher;
	int	num_switches;

	num_switches = 0;
	cnt = 0;
	switcher = 0;
	while (data->combine[cnt1].combined_str[cnt] != '\0')
	{
		printf("%i %c\n", numb[cnt], data->combine[cnt1].combined_str[cnt]);
		if (numb[cnt] == 1 || numb[cnt] == '|')
			switcher = numb[cnt];
		else
			switcher = 0;
		numb1[cnt] = switcher;
		cnt++;
	}
	count_switcher(data, numb1, cnt1);
	if (create_tks(data, numb1, cnt1) == ERROR) // @todo free all tokens in case of malloc failiure beforehand
		return (ERROR);
	return (EXECUTED);
}

void	lex_norm_helper(t_data *data, int cnt1, int *numb, int quote_state)
{
	int	cnt;

	cnt = 0;
	while (data->combine[cnt1].combined_str[cnt] != '\0')
	{
		quote_state = q_state(data->combine[cnt1].combined_str,
				cnt, quote_state);
		numb[cnt] = quote_state;
		if (quote_state == 0 && (data->combine[cnt1].combined_str[cnt] == 34
				|| data->combine[cnt1].combined_str[cnt] == 39))
			numb[cnt] = data->combine[cnt1].combined_str[cnt];
		if ((data->combine[cnt1].combined_str[cnt] == '<'
				|| data->combine[cnt1].combined_str[cnt] == '>'
				|| data->combine[cnt1].combined_str[cnt] == '|'
				|| data->combine[cnt1].combined_str[cnt] == '$')
			&& quote_state < 30)
			numb[cnt] = data->combine[cnt1].combined_str[cnt];
		if (numb[cnt] == 0)
			numb[cnt] = is_white_space(data->combine[cnt1].combined_str[cnt]);
		cnt++;
	}
}

int	create_blobs(t_data *data, int cnt1, int quote_state)
{
	int	*numb;
	int	*numb1;

	numb = NULL;
	numb = malloc(sizeof(int) * ft_strlen(data->combine[cnt1].combined_str));
	if (numb == NULL)
		return (ERROR);
	numb1 = NULL;
	numb1 = malloc(sizeof(int) * ft_strlen(data->combine[cnt1].combined_str));
	if (numb1 == NULL)
		return (free(numb), ERROR);
	lex_norm_helper(data, cnt1, numb, quote_state);
	if (operations_with_blob(data, numb, cnt1, numb1) == ERROR)
		return (free(numb), free(numb1), ERROR);
	return (free(numb), free(numb1), EXECUTED);
}

int	create_tokens(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cnt < data->commands_to_process)
	{
		if (create_blobs(data, cnt, 0) == ERROR)
			return (ERROR);
		cnt++;
	}
	return (EXECUTED);
}
