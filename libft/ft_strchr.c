/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:31:24 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/10 09:46:52 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	h;

	h = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == h)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

//#include <stdio.h>
//int main (void)
//{
//	printf("%d\n", *(ft_strchr("teste", 1024)));
//}