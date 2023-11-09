#include <mlx.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_data;


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

void	ft_mlx_pxl_draw_addr(t_data *img, char *addr, int color)
{
	int		i;

	i = img->bpp - 8;
	while (i >= 0)
	{
		if (img->endian == 1)
			*addr++ = (color >> i) & 0xFF;
		else
			*addr++ = (color >> ((img->bpp - 8) - i)) & 0xFF;
		i = i - 8;
	}
}

void	ft_draw_straight_line(t_data *img, int dy, char *addr)
{
	int	i;

	i = 0;
	if (dy < 0)
		dy *= -1;
	while (i < dy)
	{
		addr += img->ll;
		i++;
		ft_mlx_pxl_draw_addr(img, addr, 0x00FFFFFF);
	}
}

void	ft_draw_angle_line(t_data *img, int dx, int dy, char *addr)
{
	int	error;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	if (dy != 0 && dx != 0 && (dy / dx < 0))
		sign = -1;
	if (dy < 0)
		dy = dy * -1;
	if (dx < 0)
		dx = dx * - 1;
	error = dx / 2;
	while (i != dx)
	{
		addr = addr + (img->bpp / 8);
		if (error - dy <= 0)
		{
			addr += img->ll * sign;
			error += dx;
		}
		ft_mlx_pxl_draw_addr(img, addr, 0x00FFFFFF);
		i++;
		error -= dy;
	}
}


char *ft_draw(int *p1, int *p2, t_data *img)
{
	char *addr;

	// p1[1] += p1[2];
	// p2[1] += p2[2];
	if (p2[1] - p1[1] / p2[0] - p1[0] >= 0)
		addr = img->addr + (((img->bpp / 8) * p2[0]) + (img->ll * p2[1]));
	else
		addr = img->addr + (((img->bpp / 8) * p1[0]) + (img->ll * p1[1]));
	if (p1[0] - p2[0] != 0)
		ft_draw_angle_line(img, p1[0] - p2[0], p1[1] - p2[1], addr);
	else
		ft_draw_straight_line(img, p1[1] - p2[1], addr);
	ft_mlx_pxl_draw_pos(img, p1[0], p1[1], 0x00FF0000);
	ft_mlx_pxl_draw_pos(img, p2[0], p2[1], 0x00FF0000);
}

int main(void)
{
	void *mlx;
	t_data img;
	void *mlx_window;
	int i = 0;
	int *p2;
	int *p1;

	p1 = malloc(sizeof(int) * 2);
	p2 = malloc(sizeof(int) * 2);
	p1[0] = 400;
	p1[1] = 200;
	p2[0] = 300;
	p2[1] = 100;
	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "hi");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, 
		&img.endian); 
	ft_draw(p1, p2, &img);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}