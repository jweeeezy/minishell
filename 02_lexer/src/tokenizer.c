/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:39:45 by kvebers           #+#    #+#             */
/*   Updated: 2023/03/05 14:01:37 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  //  needed for t_data, functions()
#include "libft.h"      //  needed for ft_strchr()

static char	**free_tokens(char **tokens)
{
	int	cnt;

	cnt = 0;
	while (tokens[cnt] != NULL)
	{
		free(tokens[cnt]);
		cnt++;
	}
	free(tokens);
	return (NULL);
}

static int	count_tokens(char *line, char *tokens)
{
	int	cnt;
	int	count_tokens;
	int	string;

	string = 0;
	count_tokens = 0;
	cnt = 0;
	while (line[cnt] != '\0')
	{
		if (ft_strchr(tokens, line[cnt])
			|| line[cnt] == 39
			|| line[cnt] == 34
			|| is_white_space(line[cnt]) == 1)
		{
			count_tokens++;
			string = 0;
		}
		else if (string == 0)
		{
			count_tokens++;
			string = 1;
		}
		cnt++;
	}
	return (count_tokens);
}

static int	count_chars(int char_counter, char *line)
{
	while (line[char_counter] != '\0'
		&& line[char_counter] != 39
		&& line[char_counter] != 34
		&& line[char_counter] != '|'
		&& line[char_counter] != '$'
		&& line[char_counter] != '<'
		&& line[char_counter] != '>'
		&& line[char_counter] != '='
		&& line[char_counter] != 32
		&& line[char_counter] != '\t'
		&& line[char_counter] != '\v'
		&& line[char_counter] != '\n'
		&& line[char_counter] != '\r'
		&& line[char_counter] != '\f')
	{
		char_counter++;
	}
	return (char_counter);
}

static char	*create_sub_string(t_data *data, int pos_1, int pos_2)
{
	char	*token;
	int		cnt;

	cnt = 0;
	token = malloc(sizeof(char) * (pos_2 - pos_1 + 1));
	if (token == NULL)
		return (NULL);
	while (pos_1 + cnt < pos_2 && data->line[pos_1 + cnt] != '\0')
	{
		token[cnt] = data->line[pos_1 + cnt];
		cnt++;
	}
	token[cnt] = '\0';
	return (token);
}

char	**tokenizer(t_data *data, int cnt, int char_counter, int temp_char)
{
	//	@note same name as int data->tokens, which is an int
	char	**tokens;

	data->tokens = count_tokens(data->line, "<>=$|");
	tokens = malloc(sizeof(char *) * (data->tokens + 1));
	if (tokens == NULL)
		return (NULL);
	while (cnt < data->tokens)
	{
		char_counter = count_chars(char_counter, data->line);
		if (temp_char == char_counter)
			char_counter++;
		tokens[cnt] = create_sub_string(data, temp_char, char_counter);
		if (tokens[cnt] == NULL)
		{
			free_tokens(tokens);
			return (NULL);
		}
		temp_char = char_counter;
		cnt++;
	}
	tokens[cnt] = NULL;
	return (tokens);
}
