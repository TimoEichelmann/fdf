/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:28:27 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/14 12:18:15 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if ((unsigned char)s2[i] == '\0' || i == n)
		return (0);
	else
		return (0 - (unsigned char)s2[i]);
}

//#include <stdio.h>
//int main(void)
//{
//	unsigned char c = '\200';
//	printf("%i\n", ft_strncmp("test\200", "test\0", 6));
//	printf("%i\n", c);
//}