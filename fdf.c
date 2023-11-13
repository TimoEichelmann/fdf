#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}t_data;

typedef struct	s_point {
	int	x;
	int	y;
	// int	z;
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

void	ft_copy_grid(int ***result, int **grid, int len)
{
	int **new;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new = *result;
	while (grid[j][i])
	{
		new[j][i] = grid[j][i];
		if (i == len)
		{
			i = 0;
			j++;
		}
		i++;
	}
}

int	*ft_create_grid_line(char ***s)
{
	char	**splitted;
	int		*result;
	int		i;

	i = 0;
	splitted = *s;
	while (splitted[i])
		i++;
	result = malloc(sizeof(int) * i);
	i = 0;
	while (splitted[i])
	{
		result[i] = ft_atoi(splitted[i]);
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (result);
}

int	**ft_transform(int ***o_g, char **line, int row)
{
	int		**grid;
	char	**splitted;
	int		i;
	int		**old_grid;

	i = 0;
	grid = malloc(sizeof(int *) * row + 1);
	if (row != 0)
	{
		old_grid = *o_g;
		while (i < row)
		{
			grid[i] = old_grid[i];
			i++;
		}
		free(old_grid);
	}
	splitted = ft_split(*line, ' ');
	free(*line);
	grid[i] = ft_create_grid_line(&splitted);
	printf("%d", grid[i][0]);
	// int	j = 0;
	// while (grid[i][j])
	// {
	// 	printf("%d\n", grid[i][j]);
	// 	j++;
	// }
	// int j = 0;
	// printf("%d", grid[i][0]);
	// while (grid[i][j])
	// {
		// printf("%d", grid[i][j]);
	// 	j++;
	// }
	return (grid);
}

int	**ft_initialize(int fd)
{
	int	**grid;
	char	*line;
	// int		**grid;
	int		i;

	i = 0;
	line = "hi";
	grid = NULL;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			grid = ft_transform(&grid, &line, i);
		i++;
	}
	i = 0;
	free(line);
	// if (grid == NULL)
	// 	return (NULL);
	// return (grid);
	return (grid);
}

int main(int argc, char **argv)
{
	// void *mlx;
	// t_data img;
	// void *mlx_window;
	int		fd;
	int		**grid;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	// mlx = mlx_init();
	// mlx_window = mlx_new_window(mlx, 1000, 1000, "hi");
	// img.img = mlx_new_image(mlx, 1000, 1000);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	// &img.endian);
	grid = ft_initialize(fd);
	free(grid);
	// mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	// mlx_loop(mlx);
}