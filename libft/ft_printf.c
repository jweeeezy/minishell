/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:32:36 by kvebers           #+#    #+#             */
/*   Updated: 2022/12/06 11:50:06 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lunch_args(const char str, va_list args)
{
	int	args_len;

	args_len = 0;
	if (str == 'c')
		args_len = ft_putchar(va_arg(args, int));
	else if (str == 's')
		args_len = ft_putstr(va_arg(args, char *));
	else if (str == 'p')
		args_len = ft_putptr(va_arg(args, unsigned long));
	else if (str == 'd')
		args_len = ft_putdeca(va_arg(args, int));
	else if (str == 'i')
		args_len = ft_putdeca(va_arg(args, int));
	else if (str == 'u')
		args_len = ft_putunsigned(va_arg(args, unsigned int));
	else if (str == 'x')
		args_len = ft_puthex(va_arg(args, unsigned int), 'a' - 10);
	else if (str == 'X')
		args_len = ft_puthex(va_arg(args, unsigned int), 'A' - 10);
	else if (str == '%')
		args_len = ft_putchar('%');
	return (args_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		out_len;
	int		cnt;

	out_len = 0;
	cnt = 0;
	va_start(args, str);
	while (*(str + cnt) != '\0')
	{
		if (*(str + cnt) == '%')
		{
			cnt++;
			out_len = out_len + ft_lunch_args(*(str + cnt), args);
		}
		else
		{
			out_len++;
			ft_putchar_fd(*(str + cnt), 1);
		}
		cnt++;
	}
	va_end(args);
	return (out_len);
}
