/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:11:55 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/09 17:55:05 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_pos(int	num)
{
	if (num < 0)
		return (num * -1);
	else
		return (num);
}

void	ft_plot(t_point *plot, t_point *p1, char ind)
{
	plot->x = p1->x;
	plot->z = p1->z;
	plot->max_height = p1->max_height;
	plot->height = p1->height;
	if (ind == 'l')
		plot->x++;
	else
		plot->z++;
}

void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int sign;
	t_point plot;
	double	color;

	sign = 1;
	if (p2->z - p1->z < 0)
		sign = -1;
	color = 0xFF0000 + ((255.0 * (p1->height / p1->max_height)));
	error = (2 * ft_pos(p2->z - p1->z)) - (p2->x - p1->x);
	ft_plot(&plot, p1, 'l');
	while (plot.x != p2->x)
	{
		if (error > 0)
		{
			plot.z += sign;
			error += (2 * ((ft_pos(p2->z - p1->z)) - (p2->x - p1->x)));
			if (p1->height != p2->height)
				color -= ((sign * (255.0 * (ft_pos(p1->height - p2->height) / p1->max_height)) / ft_pos(p1->z - p2->z)));
		}
		else
			error += 2 * ft_pos(p2->z - p1->z);
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, ft_round(color));
		plot.x++;
	}
}

void	ft_draw_high_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int sign;
	t_point plot;
	double	color;

	sign = 1;
	color = 0xFF00FF - ((255.0 * (1 - (p1->height / p1->max_height))));
	if (p2->x - p1->x < 0)
		sign = -1;
	error = (2 * ft_pos(p2->x - p1->x)) - (p2->z - p1->z);
	ft_plot(&plot, p1, 'h');
	while (plot.z != p2->z)
	{
		if (error > 0)
		{
			plot.x += sign;
			error += (2 * ((ft_pos(p2->x - p1->x)) - (p2->z - p1->z)));
		}
		else
			error += 2 * ft_pos(p2->x - p1->x);
		if (p1->height != p2->height)
			color -= (255.0 * (ft_pos(p1->height - p2->height) / p1->max_height)) / ft_pos(p1->z - p2->z);
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, ft_round(color));
		plot.z++;
	}
}

// int	ft_color(t_point *plot)
// {
// 	int	color;
	
// 	color = 0x000000FF;
// 	plot->height
// }

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
	ft_mlx_pxl_draw_pos(img, p1->x, p1->z, (0xFF0000 + (255.0 * (p1->height / p1->max_height))));
	ft_mlx_pxl_draw_pos(img, p2->x, p2->z, (0xFF0000 + (255.0 * (p2->height / p2->max_height))));
}