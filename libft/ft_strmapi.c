/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:50:49 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/14 15:26:29 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*result;

	i = 0;
	if (!(s) || !(f))
		return (0);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (0);
	ft_memcpy(result, s, ft_strlen(s));
	while (s[i])
	{
		result[i] = (*f)(i, result[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
