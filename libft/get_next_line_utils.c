/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:00:29 by marvin            #+#    #+#             */
/*   Updated: 2023/02/17 12:06:04 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin_gnl(char *stash, char *buf)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = -1;
	if (!stash)
	{
		stash = malloc((sizeof(char) * 1));
		stash[0] = '\0';
	}
	result = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!result)
		return (NULL);
	while (stash[++i])
		result[i] = stash[i];
	while (buf[++j])
		result[i + j] = buf[j];
	result[i + j] = '\0';
	free(stash);
	return (result);
}

int	ft_nl_check(char *p)
{
	int	i;

	i = 0;
	if (!p)
		return (0);
	while (p[i])
	{
		if (p[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
