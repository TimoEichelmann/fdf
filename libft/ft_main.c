/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:36:18 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/13 13:07:28 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_printstr(char *p)
{
	int	i;

	i = 0;
	if (!p)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (p[i])
	{
		write(1, &p[i], 1);
		i++;
	}
	return (i);
}

int	ft_printchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_format(const char *p, va_list args, int i, int result)
{
	if (p[i + 1] == 'c')
		result = result + ft_printchar(va_arg(args, int));
	if (p[i + 1] == 's')
		result = result + ft_printstr(va_arg(args, char *));
	if (p[i + 1] == 'p')
		result = result + ft_void_pointer(va_arg(args, void *));
	if ((p[i + 1] == 'd') || (p[i + 1] == 'i'))
		result = result + ft_int(va_arg(args, int));
	if (p[i + 1] == 'u')
		result = result + ft_unsigned_int(va_arg(args, unsigned int));
	if ((p[i + 1] == 'x') || (p[i + 1] == 'X'))
		result += ft_hexconverter(va_arg(args, unsigned int), p, i);
	if (p[i + 1] == '%')
		result = result + ft_printchar('%');
	return (result);
}

int	ft_printf(const char *p, ...)
{
	va_list			args;
	int				i;
	int				result;
	int				temp;

	result = 0;
	temp = 0;
	i = 0;
	va_start(args, p);
	while (p[i])
	{
		if (p[i] == '%')
		{
			temp = ft_format(p, args, i, temp);
			i = i + 1;
		}
		else
			result = result + write (1, &p[i], 1);
		result = result + temp;
		temp = 0;
		i++;
	}
	va_end(args);
	return (result);
}
