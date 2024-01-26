/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:39:33 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/08 14:00:23 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!(little[j]))
		return ((char *) big);
	while (big[i] && i < len)
	{
		while (big[i] == little[j] && i < len)
		{
			if (!(little[j + 1]))
				return ((char *)big + i - j);
			i++;
			j++;
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (0);
}

//#include <stdio.h>

//int main (void)
//{
//	char haystack[30] = "aaabcabcd";
//	//char needle[10] = "aabc";
//	// char * empty = (char*)"";
//	 printf("%c\n", *ft_strnstr(haystack, "a", 1));

//}