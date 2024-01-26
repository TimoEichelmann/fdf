/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:19:40 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/08 13:05:50 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	h;

	h = c;
	i = 0;
	while (s[i])
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == h)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

//#include <stdio.h>
//int main (void)
//{
//	char s[] = "";
//	printf("%c", *ft_strrchr(s, 0));
//}