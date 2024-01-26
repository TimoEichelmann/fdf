/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexnmbs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:53:18 by marvin            #+#    #+#             */
/*   Updated: 2023/01/12 16:43:01 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexadecimal_len(unsigned int h)
{
	int		result_len;

	result_len = 0;
	while (h / 16 != 0)
	{
		h = h / 16;
		result_len++;
	}
	return (result_len);
}

int	ft_hexadecimal_len_long(unsigned long int h)
{
	int		result_len;

	result_len = 0;
	while (h / 16 != 0)
	{
		h = h / 16;
		result_len++;
	}
	return (result_len);
}

int	ft_hexconverter(unsigned int h, const char *p, int u)
{
	char		*base;
	char		*result;
	int			len;
	int			i;

	base = "0123456789ABCDEF";
	if (p[u + 1] == 'x')
		base = "0123456789abcdef";
	i = 0;
	len = ft_hexadecimal_len(h);
	result = malloc(len + 2);
	while (i <= len)
	{
		result[len - i] = base[h % 16];
		h = h / 16;
		i++;
	}
	result[i] = 0;
	ft_printstr(result);
	free(result);
	return (len + 1);
}

int	ft_hexconverter_long(unsigned long long int h)
{
	char	*base;
	char	*result;
	int		len;
	int		i;

	base = "0123456789abcdef";
	i = 0;
	len = ft_hexadecimal_len_long(h);
	result = malloc(len + 2);
	while (i <= len)
	{
		result[len - i] = base[h % 16];
		h = h / 16;
		i++;
	}
	result[i] = 0;
	ft_printstr("0x");
	ft_printstr(result);
	free(result);
	return (len + 3);
}

int	ft_void_pointer(void *p)
{
	long long unsigned int	j;

	if (p == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	j = *(unsigned long int *) &p;
	return (ft_hexconverter_long(j));
}
