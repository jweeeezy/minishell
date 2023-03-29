/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/29 19:59:11 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	kindergarden_meth_2(char *str, int counter)
{
	int	sign;
	int	cnt;

	cnt = 5;
	sign = 0;
	while (str[cnt] != '\0' && counter != sign)
	{
		if (str[cnt] == '-')
			sign++;
		cnt++;
	}
	while (str[cnt] != '\0' && (str[cnt] == 'n'
			|| is_white_space(str[cnt]) == ADD))
		cnt++;
	return (cnt);
}

int	kindergarden_meth(int *numbered, char *str, int cnt)
{
	int	apple_count;
	int	sign;

	apple_count = 0;
	sign = 0;
	while (str[cnt] != '\0')
	{
		if (numbered[cnt] == 3 || numbered[cnt] == 11)
			sign++;
		if (numbered[cnt] != -1 && numbered[cnt] != 1)
			apple_count++;
		cnt++;
	}
	return (sign);
}

void	echo_n(t_data *data, int index)
{
	int		cnt;
	char	*comb;
	int		*numbered;

	comb = NULL;
	cnt = data->combine[index].command->number;
	comb = echo_n_helper(data, cnt, comb);
	if (comb == NULL)
		return (*NULL);
	comb = echo_merge(comb, 0, 0);
	numbered = malloc(sizeof(int) * ft_strlen(comb));
	if (numbered == NULL)
		return (free(comb), *NULL);
	num_echo(numbered, comb, 0, 0);
	renumber_echo(numbered, comb, 0);
	cnt = kindergarden_meth(numbered, comb, 0);
	if (cnt == 0)
		printf("%s\n", data->combine[index].combined_str + 5);
	else
		printf("%s", data->combine[index].combined_str
			+ kindergarden_meth_2(data->combine[index].combined_str, cnt));
	free(comb);
	free(numbered);
}

void	echo(t_combine str)
{
	printf("%s\n", str.combined_str + 5);
}
