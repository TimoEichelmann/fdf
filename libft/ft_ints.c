/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ints.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:00:34 by marvin            #+#    #+#             */
/*   Updated: 2023/01/13 13:05:02 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int(int i)
{
	char	*p;
	int		result;

	p = ft_itoa(i);
	result = (ft_printstr(p));
	free(p);
	return (result);
}

int	ft_uintlen(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len + 1);
}

char	*ft_uitoa(unsigned int i)
{
	int		len;
	char	*result;

	len = ft_uintlen(i);
	result = malloc(len + 1);
	if (!result)
		return (0);
	result[len] = '\0';
	while (i > 0)
	{
		len--;
		result[len] = i % 10 + 48;
		i = i / 10;
	}
	return (result);
}

int	ft_unsigned_int(unsigned int i)
{
	char			*p;
	int				result;

	if (i == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	p = ft_uitoa(i);
	result = ft_printstr(p);
	free(p);
	return (result);
}
