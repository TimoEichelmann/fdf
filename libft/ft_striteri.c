/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:50:29 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/10 14:28:56 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, s + i);
		i++;
	}
	s[i] = 0;
}

//void
//iter(unsigned int i, char * s) {
//	*s += i;
//}
//#include <stdio.h>
//int main (void)
//{
//	char test[] = "0000000000";
//	ft_striteri(test, iter);
//	printf("%s", test);
//}