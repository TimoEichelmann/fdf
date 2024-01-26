/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:10:43 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 20:45:51 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_determine_len(t_point **grid, double *len, int row, int ll)
{
	if (grid[row][ll].z > grid[0][ll].x)
	{
		*len = 500.0 / (grid[row][ll].z);
		if (grid[row][ll].m_h > grid[row][ll].z)
		{
			*len = 500.0 / grid[row][ll].m_h;
			return (grid[0][0].m_h - 1);
		}
		return (-1);
	}
	else
	{
		*len = 500.0 / (grid[0][ll].x);
		if (grid[row][ll].m_h > grid[0][ll].x)
		{
			*len = 500.0 / grid[row][ll].m_h;
			return (grid[0][0].m_h);
		}
	}
	return (1);
}

void	ft_vectorize(t_point **grid, int row, int ll)
{
	double	len;
	double	h;
	double	width;
	int		ind;

	ft_gradient(grid);
	ind = ft_determine_len(grid, &len, row, ll);
	h = ft_pos(grid[0][0].z - grid[row][ll].z) / 2.0;
	width = ft_pos(grid[0][ll].x - grid[row][0].x) / 2.0;
	row = 0;
	ll = 0;
	while (grid[row])
	{
		while (grid[row][ll].end)
		{
			grid[row][ll].x = ft_round((grid[row][ll].x * len) 
					+ 350 - width * len);
			grid[row][ll].z = ft_round((grid[row][ll].z * len) 
					+ 350 - h * len + ind);
			grid[row][ll].y *= len;
			ll++;
		}
		row++;
		ll = 0;
	}
}

void	ft_iso(t_point *p)
{
	double	x;
	double	y;
	double	z;

	x = cos(RAD) * p->x - sin(RAD) * p->y;
	y = sin(RAD) * p->x + cos(RAD) * p->y;
	p->x = x;
	y = cos(RAD2) * y - sin(RAD2) * p->z;
	z = sin(RAD2) * y + cos(RAD2) * p->z;
	p->z = z;
}
