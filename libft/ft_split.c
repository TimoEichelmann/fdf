/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:22:11 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/04 14:35:14 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:22:11 by teichelm          #+#    #+#             */
/*   Updated: 2022/12/16 16:50:25 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

static int	ft_word_count(char *s, char c)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word_count);
}

static int	ft_word_len(char *s, int i, char c)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	p = malloc(sizeof(char *) * (ft_word_count((char *) s, c) + 1));
	if (!p)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			p[j] = ft_substr(s, i, (ft_word_len((char *)s, i, c) - i));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	p[j] = NULL;
	return (p);
}
