#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// void	ft_escape()
// {
// 	if (keycode == )
// 		exit (0);
// 	param = NULL;
// }

void	ft_mlx_pxl_draw_pos(t_data *img, int x, int y, int color)
{
	char 	*pxl;
	int		i;

	i = img->bits_per_pixel - 8;
	pxl = img->addr + (((img->bits_per_pixel / 8) * x) + (img->line_length * y));
	while (i >= 0)
	{
		if (img->endian == 1)
			*pxl++ = (color >> i) & 0xFF;
		else
			*pxl++ = (color >> ((img->bits_per_pixel - 8) - i)) & 0xFF;
		i = i - 8;
	}
}

void	ft_mlx_pxl_draw_addr(t_data *img, char *addr, int color)
{
	int		i;

	i = img->bits_per_pixel - 8;
	while (i >= 0)
	{
		if (img->endian == 1)
			*addr++ = (color >> i) & 0xFF;
		else
			*addr++ = (color >> ((img->bits_per_pixel - 8) - i)) & 0xFF;
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
		addr += img->line_length;
		i++;
		ft_mlx_pxl_draw_addr(img, addr, 0x00FFFFFF);
	}
}

void	ft_draw_angle_line(t_data *img, int dx, int dy, int fin_x, char *addr)
{
	int	error;
	int	i;
	int	sign;

	sign = 1;
	if (dy != 0 && dx != 0 && (dy / dx < 0))
		sign = -1;
	if (dy < 0)
		dy = dy * -1;
	if (dx < 0)
		dx = dx * - 1;
	i = fin_x + dx * (-1);
	error = dx / 2;
	while (i != fin_x)
	{
		addr = addr + (img->bits_per_pixel / 8);
		if (error - dy <= 0)
		{
			addr += img->line_length * sign;
			error += dx;
		}
		ft_mlx_pxl_draw_addr(img, addr, 0x00FFFFFF);
		i++;
		error -= dy;
	}
}

int main(void)
{
	void *mlx;
	t_data img;
	void *mlx_window;
	int i = 0;
	int p2[2] = {400, 300};
	int p1[2] = {400, 400};

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "hi");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, 
		&img.endian);
	char *addr = img.addr + (((img.bits_per_pixel / 8) * p1[0]) + (img.line_length * p1[1])); 
	
	ft_mlx_pxl_draw_pos(&img, p1[0], p1[1], 0x00FF0000);
	if (p1[0] - p2[0] != 0)
		ft_draw_angle_line(&img, p1[0] - p2[0], p1[1] - p2[1], p2[0], addr);
	else
		ft_draw_straight_line(&img, p1[1] - p2[1], addr);
	
	ft_mlx_pxl_draw_pos(&img, p2[0], p2[1], 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}