/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:02:03 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/14 14:33:12 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	else
		len = ft_strlen((char *)s2);
	p = malloc(len + 1);
	if (!p)
		return (0);
	while (s1[i++])
		p[i] = s1[i];
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = 0;
	return (p);
}
