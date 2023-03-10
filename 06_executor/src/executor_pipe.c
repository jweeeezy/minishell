/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:35:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/03/10 18:55:45 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

int	executor_pipe(t_data *data, int cnt)
{
	t_vector_str	vector_cmd;
	t_execute		*offset;
	int				index;

	index = 0;
	offset = data->execute[cnt];
	while (data->execute[index] != offset)
	{
		
	}
	// prepare pipes
