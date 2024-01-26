/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:10:31 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/16 15:52:47 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_intlen(int nb)
{
	int	len;

	len = 0;
	while (nb >= 10 || nb <= -10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static void	ft_convert(int nb, char *p)
{
	int	offset;

	offset = 0;
	if (nb == -2147483648)
		nb = -2147483647;
	if (nb < 0)
	{
		*p = '-';
		p++;
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_convert(nb / 10, p);
		offset = ft_intlen(nb);
		nb = nb % 10;
	}
	if (nb < 10)
		p[offset] = nb + 48;
}

char	*ft_itoa(int n)
{
	char	*p;
	int		size;

	size = ft_intlen(n);
	if (n < 0)
		size++;
	p = malloc(size + 2);
	if (!p)
		return (0);
	ft_convert(n, p);
	p[size + 1] = 0;
	if (n == -2147483648)
		p[10] = '8';
	return (p);
}

//#include <stdio.h>
//int main()
//{
//	printf("%s\n", ft_itoa(-10));
//}