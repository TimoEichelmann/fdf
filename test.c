#include <mlx.h>
#include <stdlib.h>
// #include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#define RAD 0.785398
#define RAD2  0.615473

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
}t_point;

void	ft_draw_low_line(t_data *img, int dx, int dy, char *addr, int sign, int color)
{
	double	error;
	int	i;

	i = 0;
	error = dy / 2;

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

typedef struct s_plot {
	int	x;
	int	z;
	int d1;
	int	d2;
}t_plot;

void	ft_plot(t_point *plot, t_point *p1, t_point *p2)
{
	plot->d1 = ft_pos(p1->z - p2->z) * -1;
	plot->d2 = p1->x - p2->x;
	plot->x = p1.x;
	plot->z = p1.z;
	if (p1.x > p2.x)
	{
		plot->x = p2.x;
		plot->z = p2.z;
	}
	if (ft_pos(p1->x - p2->x) > ft_pos(p1->z - p2->z))
	{
		plot->d1 = p1->x - p2->x;
		plot->d2 = ft_pos(p1->z - p2->z) * -1;
	}
}

void	ft_draw_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int	i;
	t_plot plot;
	int	*fast;
	int	*slow;

	ft_plot(plot, p1, p2);
	error = plot.d1 / 2;
	while (i != ft_pos(plot.d1))
	{
		if (error - plot.d2 <= 0)
		{
			slow++;
			error += plot.d1;
		}
		ft_mlx_pxl_draw_pos(img, plot.x, ft_pos(plot.z), color);
		i++;
		error -= plot.d2;
		fast++;
	}
}

void	ft_draw_angle_line(t_data *img, int dx, int dy, char *addr, int sign, int color)
{
	double	error;
	int	i;

	i = 0;
	if (dx < dy)
	{
		ft_draw_low_line(img, dx, dy, addr, sign, color);
		return ;
	}
	error = dx / 2;
	while (i != dx)
	{
		if (error - dy <= 0)
		{
			addr += (img->ll * sign);
			error += dx;
		}
		ft_mlx_pxl_draw_addr(img, addr, color);
		i++;
		addr = addr + (img->bpp / 8);
		error -= dy;
	}
}
