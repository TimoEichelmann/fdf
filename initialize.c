/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:09:20 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 20:23:43 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_insert(char **splitted, t_point *line, int row)
{
	int	i;

	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		line[i].z = -ft_atoi(splitted[i]);
		line[i].y = row;
		line[i].x = i;
		line[i].h = ft_atoi(splitted[i]);
		line[i].end = 1;
		i++;
	}
	line[i].end = 0;
}

void	ft_offset(t_point **grid, double leftmost)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			grid[i][j].x -= leftmost;
			j++;
		}
		i++;
		j = 0;
	}
}

void	ft_coordinates(t_point	**grid)
{
	int		row;
	int		line;
	int		ll;
	double	leftmost;

	row = 0;
	line = 0;
	leftmost = 0;
	while (grid[row])
	{
		while (grid[row][line].end)
		{
			ft_iso(&grid[row][line]);
			if (grid[row][line].x < leftmost)
				leftmost = grid[row][line].x;
			line++;
		}
		row++;
		ll = line;
		line = 0;
	}
	ft_offset(grid, leftmost);
	ft_vectorize(grid, row - 1, ll - 1);
}

t_point	**ft_transform(char *str, int rows)
{
	t_point	**result;
	int		i;
	int		len;
	char	**splitted;

	i = 0;
	splitted = ft_split(str, ' ');
	ft_check_map(splitted, str);
	result = malloc(sizeof(t_point *) * (rows + 1));
	while (splitted[i] && splitted[i][0] != '\n')
		i++;
	len = i + 1;
	free(str);
	i = 0;
	while (i < rows)
	{
		result[i] = malloc(sizeof(t_point) * (len + 1));
		ft_insert(splitted + (i * len), result[i], i);
		i++;
	}
	result[i] = NULL;
	ft_free_splitted(splitted);
	return (result);
}

t_point	**ft_initialize(int fd)
{
	t_point	**grid;
	char	*line;
	char	*stash;
	int		i;

	i = -1;
	stash = NULL;
	grid = NULL;
	while (fd)
	{
		line = get_next_line(fd);
		if (line == NULL)
			fd = close(fd);
		if (line != NULL)
			stash = ft_join(stash, line);
		if (stash == NULL)
			return (NULL);
		i++;
	}
	stash = ft_line_modify(stash);
	grid = ft_transform(stash, i);
	ft_coordinates(grid);
	return (grid);
}
