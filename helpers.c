/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:06:23 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 20:41:21 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_pos(int num)
{
	if (num < 0)
		return (num * -1);
	else
		return (num);
}

void	ft_gradient(t_point **grid)
{
	int	i;
	int	j;
	int	m_h;

	m_h = 0;
	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			if (m_h < grid[i][j].h)
				m_h = grid[i][j].h;
			j++;
		}
		j = 0;
		i++;
	}
	ft_max_height(grid, m_h);
}

double	ft_round(double num)
{
	if (num - (int)num >= 0.5)
		return ((int)num + 1);
	else
		return ((int)num);
}

void	ft_max_height(t_point **grid, int max)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (max == 0)
		max = 1;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			grid[i][j].m_h = max;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}
