/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:54:14 by teichelm          #+#    #+#             */
/*   Updated: 2022/11/30 16:34:01 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *str, unsigned int len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (len--)
	{
		*ptr++ = 0;
	}
	return ;
}
