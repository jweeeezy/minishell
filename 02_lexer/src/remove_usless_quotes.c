/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_usless_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:28 by kvebers           #+#    #+#             */
/*   Updated: 2023/04/03 12:14:10 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	remove_usless_quotes(t_data *data, int quote_state, int cnt)
{
	char	*temp;

	temp = NULL;
	while (data->line[cnt] != '\0')
	{
		quote_state = echo_n_quote_state(data->line, cnt, quote_state);
		if (data->line[cnt + 1] != '\0' && quote_state == 0
			&& (data->line[cnt] == 34 || data->line[cnt] == 39)
			&& data->line[cnt + 1] == data->line[cnt])
		{
			cnt++;
			quote_state = echo_n_quote_state(data->line, cnt, quote_state);
		}
		else
		{
			temp = ft_charjoin(temp, data->line[cnt], 0, 0);
			if (temp == NULL)
				return (ERROR);
		}
		cnt++;
	}
	free(data->line);
	data->line = temp;
	return (EXECUTED);
}

void	remove_usless_quotes4(char *str, int *numb, int cnt)
{
	t_dump	quotes;

	(void) str;
	quotes.a = numb[cnt];
	quotes.b = numb[cnt + 1];
	quotes.c = numb[cnt + 2];
	quotes.d = numb[cnt + 3];
	if (quotes.a > 30 && quotes.a == quotes.b && quotes.c == 0)
	{
		numb[cnt] = 3;
		numb[cnt + 1] = 3;
	}
}

void	remove_usless_quotes3(char *str, int *numb, int cnt)
{
	t_dump	quotes;

	while (str[cnt + 3] != '\0')
	{
		quotes.a = numb[cnt];
		quotes.b = numb[cnt + 1];
		quotes.c = numb[cnt + 2];
		quotes.d = numb[cnt + 3];
		if (quotes.b > 30 && quotes.b == quotes.c
			&& (quotes.a == 0 || quotes.d == 0)
			&& (quotes.a != quotes.b && quotes.d != quotes.b))
		{
			numb[cnt + 1] = 3;
			numb[cnt + 2] = 3;
		}
		cnt++;
	}
	remove_usless_quotes4(str, numb, 0);
}

int	remove_usless_quotes2(t_data *data, int quote_state, int cnt)
{
	int		*numb;

	numb = NULL;
	if (ft_strlen(data->line) < 4)
		return (EXECUTED);
	numb = malloc(sizeof(int) * ft_strlen(data->line));
	if (numb == NULL)
		return (EXECUTED);
	while (data->line[cnt] != '\0')
	{
		quote_state = echo_n_quote_state(data->line, cnt, quote_state);
		numb[cnt] = quote_state;
		if (numb[cnt] == 0
			&& (data->line[cnt] == 34 || data->line[cnt] == 39))
			numb[cnt] = data->line[cnt];
		else if (numb[cnt] == 0)
			numb[cnt] = is_white_space(data->line[cnt]);
		cnt++;
	}
	remove_usless_quotes3(data->line, numb, 0);
	data->line = remove_usless_quotes5(data->line, numb, 0);
	if (data->line == NULL)
		return (free(numb), ERROR);
	return (free(numb), EXECUTED);
}
