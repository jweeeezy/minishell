/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:12 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/29 18:02:31 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	kindergarden_meth(int *numbered, char *str, int cnt)
{
	int	apple_count;
	int sign;

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
	if (sign > 0)
		return (apple_count);
	else
		return (5);
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
		return (*NULL);
	num_echo(numbered, comb, 0, 0);
	renumber_echo(numbered, comb, 0);
	cnt = 0;
	printf("%s", data->combine[index].combined_str
		+ kindergarden_meth(numbered, comb, 0));
	if (kindergarden_meth(numbered, comb, 0) == 5)
		printf("\n");
	free(comb);
	free(numbered);
}

void	echo(t_combine str)
{
	printf("%s\n", str.combined_str + 5);
}
