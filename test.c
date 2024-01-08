#include <mlx.h>
#include <stdlib.h>
// #include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
}t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}t_data;

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
	if (ind == 'l')
		plot->x++;
	else
		plot->z++;
}

void	ft_draw_high_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int sign;
	t_point plot;

	sign = 1;
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
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, 0x00FF0000);
		plot.z++;
	}
}

void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2)
{
	int	error;
	int sign;
	t_point plot;

	sign = 1;
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
		}
		else
			error += 2 * ft_pos(p2->z - p1->z);
		ft_mlx_pxl_draw_pos(img, plot.x, plot.z, 0x00FF0000);
		plot.x++;
	}
}

void	ft_draw_line(t_data *img, t_point *p1, t_point *p2)
{
	if (ft_pos(p2->z - p1->z) < ft_pos(p2->x - p1->x))
	{
		write(1, "l", 1);
		if (p1->x > p2->x)
			ft_draw_low_line(img, p2, p1);
		else
			ft_draw_low_line(img, p1, p2);
	}
	else
	{
		write(1, "h", 1);
		if (p1->z > p2->z)
			ft_draw_high_line(img, p2, p1);
		else
		{
			ft_draw_high_line(img, p1, p2);
			write(1, "h2", 1);
		}
	}
}


int main(int argc, char **argv)
{
	void *mlx;
	t_data img;
	void *mlx_window;
	int		fd;
	t_point p1, p2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	&img.endian);
	mlx_window = mlx_new_window(mlx, 700, 700, "hi");
	p1.x = 600;
	p1.z = 100;
	p2.x = 100;
	p2.z = 300;
	ft_draw_line(&img, &p1, &p2);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}