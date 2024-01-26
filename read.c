/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:07:49 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 19:46:26 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_check_map(char **splitted, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (splitted[i])
	{
		while (splitted[i][j])
		{
			if (splitted[i][j] != ' ' && splitted[i][j] != '\n'
				&& !ft_isdigit(splitted[i][j]))
			{
				free(str);
				ft_free_splitted(splitted);
				ft_printf("Map contains unallowed characters.\n");
				exit (0);
			}
			j++;
		}
		i++;
		str = NULL;
		j = 0;
	}
}

void	ft_line_insert(char *line, char *result, int i, int j)
{
	while (line[i])
	{
		result[j] = line[i];
		if (line[i + 1] == '\0' && line[i] != ' ')
		{
			j++;
			result[j] = ' ';
		}
		if (line[i + 1] == '\n' && line[i] != ' ')
		{
			j = j + 3;
			result[j - 2] = ' ';
			result[j - 1] = '\n';
			result[j] = ' ';
			i++;
		}
		j++;
		i++;
	}
	result[j] = '\0';
}

char	*ft_line_modify(char *line)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i + 1] == '\n' && line[i] != ' ')
			j = j + 2;
		if (line[i + 1] == '\0' && line[i] != ' ')
			j++;
		i++;
	}
	result = malloc(ft_strlen(line) + 1 + j);
	ft_line_insert(line, result, 0, 0);
	free(line);
	return (result);
}

int	ft_space_check(char *line, char *stash)
{
	int	i;
	int	j;
	int	space_count_stash;
	int	space_count_line;

	j = 0;
	i = 0;
	space_count_line = 0;
	space_count_stash = 0;
	while (stash[i] != '\n')
	{
		if (stash[i] == ' ')
			space_count_stash++;
		i++;
	}
	while (line[j])
	{
		if (line[j] == ' ')
			space_count_line++;
		j++;
	}
	if (space_count_line != space_count_stash)
		return (0);
	return (1);
}

char	*ft_join(char *stash, char *line)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(line) + 2));
	if (stash)
		ft_strlcpy(result, stash, ft_strlen(stash));
	ft_strlcpy(result + ft_strlen(stash), line, ft_strlen(line));
	result[ft_strlen(stash) + ft_strlen(line)] = '\0';
	if (stash)
	{
		if (!ft_space_check(line, stash))
		{
			free(result);
			result = NULL;
		}
		free(stash);
	}
	free(line);
	return (result);
}
