/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:16:27 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/14 14:43:50 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_test(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		trail;
	char	*res;

	start = 0;
	trail = ft_strlen(s1) - 1;
	while (ft_test(s1[start], set) && s1[start])
		start++;
	while (s1[trail] && ft_test(s1[trail], set))
		trail--;
	if ((trail - start + 2) <= 0)
	{
		res = malloc(1);
		ft_memcpy(res, "\0", 1);
		return (res);
	}
	res = malloc((trail - start + 2));
	if (!res)
		return (0);
	ft_memcpy(res, (s1 + start), (trail - start + 1));
	res[trail - start + 1] = '\0';
	return (res);
}

//#include <stdio.h>
//#include <string.h>
//int main (void)
//{
//	char *p;
//	p = ft_strtrim("   xxx   xxx", " x");
//	printf("%s", p);
//	printf("%i\n", strcmp(p, ""));
//	free (p);
//}