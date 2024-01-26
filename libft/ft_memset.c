/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:50:20 by teichelm          #+#    #+#             */
/*   Updated: 2022/11/30 16:33:52 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *str, int c, unsigned int len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (len--)
	{
		*ptr++ = c;
	}
	return (str);
}
