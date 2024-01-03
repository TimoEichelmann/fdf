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

void	ft_plot(t_point *plot, t_point *p1, t_point *p2, char ind, int *sign)
{
	plot->x = p1->x;
	plot->z = p1->z;
	if ((c == 'l' && p2->z > p1->z) || (c == 'h' && p2->x < p1->x))
		*sign = -1;
	if ((p2.x < p1.x && c == 'l') || (p2.z < p1.z && c == 'h'))
	{
		plot->x = p2.x;
		plot->z = p2.z;
		if ((c == 'l' && p1->z > p2->z) || (c == 'h' && p1->x < p2->x))
			*sign = -1;
	}
}

void	ft_draw_high_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int	i;
	int sign;
	t_point plot;

	sign = 1;
	ft_plot(&plot, p1, p2, 'h', &sign);
	i = 0;
	error = ft_pos(p1.z - p2.z) / 2;
	while (i != ft_pos(p1.z - p2.z))
	{
		if (error - ft_pos(p1.x - p2.x) <= 0)
		{
			plot.z += (1 * sign);
			error += ft_pos(p1.z - p2.z);
		}
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, color);
		i++;
		plot.x++;
		error -= ft_pos(p1.z - p2.z);
	}
}

void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2, int bd)
{
	int	error;
	int	i;
	int sign;
	t_point plot;

	sign = 1;
	ft_plot(&plot, p1, p2, 'l', &sign);
	i = 0;
	error = ft_pos(p1.x - p2.x) / 2;
	while (i != ft_pos(p1.x - p2.x))
	{
		if (error - ft_pos(p1.z - p2.z) <= 0)
		{
			plot.z += (1 * sign);
			error += ft_pos(p1.x - p2.x);
		}
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, color);
		i++;
		plot.x++;
		error -= ft_pos(p1.x - p2.x);
	}
}

void	ft_draw_line(t_data *img, t_point *p1, t_point *p2)
{
	if (ft_pos(p1.x - p2.x) > ft_pos(p1.z - p2.z))
		ft_draw_low_line(&img, p1, p2);
	else
		ft_draw_high_line(&img, p1, p2);
}