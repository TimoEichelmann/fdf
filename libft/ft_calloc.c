/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:19:29 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/19 14:20:15 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(unsigned int memb, unsigned int size)
{
	void			*p;
	char			*c;
	unsigned int	i;

	i = 0;
	p = malloc(memb * size);
	if (!p)
		return (p);
	c = (char *)p;
	while (i < (memb * size))
	{
		c[i] = 0;
		i++;
	}
	return (p);
}
