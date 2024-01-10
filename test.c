#include <mlx.h>
#include <stdlib.h>
// #include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
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

void	ft_mlx_pxl_draw_pos(t_data *img, int x, int y, int color)
{
	char 	*pxl;
	int		i;

	i = img->bpp - 8;
	pxl = img->addr + (((img->bpp / 8) * x) + (img->ll * y));
	while (i >= 0)
	{
		if (img->endian == 1)
			*pxl++ = (color >> i) & 0xFF;
		else
			*pxl++ = (color >> ((img->bpp - 8) - i)) & 0xFF;
		i = i - 8;
	}
}

double	ft_round(double num)
{
	if (num - (int)num > 0.5)
		return ((int)num + 1);
	else
		return ((int)num);

}

void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int sign;
	t_point plot;
	double	color;

	sign = 1;
	color = 0x00FFFF00;
	if (p2->z - p1->z < 0)
		sign = -1;
	error = (2 * ft_pos(p2->z - p1->z)) - (p2->x - p1->x);
	ft_plot(&plot, p1, 'l');
	while (plot.x != p2->x)
	{
		if (error > 0)
		{
			plot.z += sign;
			error += (2 * ((ft_pos(p2->z - p1->z)) - (p2->x - p1->x)));
			if (p1->height != p2->height)
				color += 255.0 / ft_pos(p1->z - p2->z);
		}
		else
			error += 2 * ft_pos(p2->z - p1->z);
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, color);
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
	color = 0x00FFFFFF;
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
			color -= 255.0 / ft_pos(p1->z - p2->z);
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, color/*ft_color(&plot)*/);
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
	ft_mlx_pxl_draw_pos(img, p1->x, p1->z, 0x0000FFFF);
	ft_mlx_pxl_draw_pos(img, p2->x, p2->z, 0x000000FF);
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
}

int main(int argc, char **argv)
{
	void *mlx;
	t_data img;
	void *mlx_window;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	&img.endian);
	mlx_window = mlx_new_window(mlx, 700, 700, "hi");
	t_point p1, p2, p3;

	p1.x = 100;
	p1.z = 600;
	p2.x = 400;
	p2.z = 100;
	p3.x = 600;
	p3.z = 400;
	ft_draw_line(&img, &p1, &p2);
	ft_draw_line(&img, &p1, &p3);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}