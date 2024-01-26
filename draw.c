/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:11:55 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 19:42:39 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_grid(t_data *img, t_point **grid)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			if (grid[i][j + 1].end)
				ft_draw_line(img, &grid[i][j], &grid[i][j + 1]);
			if (grid[i + 1])
				ft_draw_line(img, &grid[i][j], &grid[i + 1][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_plot(t_point *plot, t_point *p1, char ind, t_point *p2)
{
	plot->x = p1->x;
	plot->z = p1->z;
	plot->m_h = p1->m_h;
	plot->h = p1->h;
	if (ind == 'l')
		plot->x++;
	else
		plot->z++;
	if (ind == 'l')
	{
		if (p2->z - p1->z < 0)
			return (-1);
		else
			return (1);
	}
	if (ind == 'h')
	{
		if (p2->x - p1->x < 0)
			return (-1);
		else
			return (1);
	}
	return (0);
}

void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2)
{
	int		error;
	int		sign;
	t_point	plot;
	double	c;

	c = 0xFF0000 + ((255.0 * (p1->h / p1->m_h)));
	error = (2 * ft_pos(p2->z - p1->z)) - (p2->x - p1->x);
	sign = ft_plot(&plot, p1, 'l', p2);
	while (plot.x != p2->x)
	{
		if (error > 0)
		{
			plot.z += sign;
			error += (2 * ((ft_pos(p2->z - p1->z)) - (p2->x - p1->x)));
			if (p1->h != p2->h)
				c -= ((sign * (255.0 * (fabs(p1->h - p2->h)
									/ p1->m_h)) / fabs(p1->z - p2->z)));
		}
		else
			error += 2 * ft_pos(p2->z - p1->z);
		ft_pxl_pos(img, plot.x, plot.z, ft_round(c));
		plot.x++;
	}
}

void	ft_draw_high_line(t_data *img, t_point *p1, t_point *p2)
{
	int		error;
	int		sign;
	t_point	plot;
	double	c;

	c = 0xFF00FF - ((255.0 * (1 - (p1->h / p1->m_h))));
	error = (2 * ft_pos(p2->x - p1->x)) - (p2->z - p1->z);
	sign = ft_plot(&plot, p1, 'h', p2);
	while (plot.z != p2->z)
	{
		if (error > 0)
		{
			plot.x += sign;
			error += (2 * ((ft_pos(p2->x - p1->x)) - (p2->z - p1->z)));
		}
		else
			error += 2 * ft_pos(p2->x - p1->x);
		if (p1->h != p2->h)
			c -= (255.0 * (fabs(p1->h - p2->h)
						/ p1->m_h)) / fabs(p1->z - p2->z);
		ft_pxl_pos(img, plot.x, plot.z, ft_round(c));
		plot.z++;
	}
}

void	ft_draw_line(t_data *img, t_point *p1, t_point *p2)
{
	if (ft_pos(p2->z - p1->z) < ft_pos(p2->x - p1->x))
	{
		if (p1->x > p2->x)
			ft_draw_low_line(img, p2, p1);
		else
			ft_draw_low_line(img, p1, p2);
	}
	else
	{
		if (p1->z > p2->z)
			ft_draw_high_line(img, p2, p1);
		else
		{
			ft_draw_high_line(img, p1, p2);
		}
	}
	ft_pxl_pos(img, p1->x, p1->z, (0xFF0000 + (255.0 * (p1->h / p1->m_h))));
	ft_pxl_pos(img, p2->x, p2->z, (0xFF0000 + (255.0 * (p2->h / p2->m_h))));
}
