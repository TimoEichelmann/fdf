/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:41:55 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/04 14:33:15 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned int		i;
	unsigned char		*str;
	unsigned char		h;

	str = (unsigned char *)s;
	h = c;
	i = 0;
	if (n == 0)
		return (0);
	while (i <= (n - 1))
	{
		if (str[i] == h)
			return ((unsigned char *)s + i);
		i++;
	}
	if (h == '\0' && str[i] == '\0')
		return ((unsigned char *)s + i);
	return (0);
}

//#include <stdio.h>
//int main ()
//{
//	printf("%p\n", ft_memchr(0x7fffdf662160, '\0', 6));
//	printf("%s\n", p);
//}