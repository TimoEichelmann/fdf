/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:55:15 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/02 17:08:49 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(void *str1, void *str2, int len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = str1;
	s2 = str2;
	while (len > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		len--;
		s1++;
		s2++;
	}
	return (0);
}

//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	int Str1[6] = {1, 1, 2, 5, 4};
//	int Str2[6] = {1, 1, 2, 6, 5};
//	printf("%d\n", my_memcmp(Str1, Str2, sizeof(Str1)));
//	printf("%d\n", memcmp(Str1, Str2, sizeof(Str1)));
//}