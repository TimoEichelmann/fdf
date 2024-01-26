/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:45:46 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/04 14:34:07 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	char			*result;

	if (!s)
		return (0);
	i = 0;
	if (start + len >= (unsigned int) ft_strlen(s) + 1)
		len = ft_strlen(s) - start;
	if (start >= (unsigned int) ft_strlen(s) + 1)
		len = 0;
	result = malloc(len + 1);
	if (!result)
		return (0);
	while (i < len && s[i])
	{
		result [i] = s[start + i];
		i++;
	}
	result [i] = 0;
	return (result);
}

//#include <stdio.h>
//#include <string.h>
//int main (void)
//{
//	char *res;

//	res = ft_substr("hola", 5, 2);
//	printf("%s\n", res);
//	printf("%i\n", strcmp(res, "tripouille"));
//	free(res);
//}