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

char	*ft_join(char *stash, char *line)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(line) + 2));
	if (stash)
		ft_strlcpy(result, stash, ft_strlen(stash));
	ft_strlcpy(result + ft_strlen(stash), line, ft_strlen(line));
	result[ft_strlen(stash) + ft_strlen(line)] = '\0';
	while (result[i] != '\n')
		i++;
	if ((ft_strlen(line) != i + 1 && ft_strchr(line, '\n') != 0) || 
		(ft_strlen(line) != i && ft_strchr(line, '\n') == 0))
	{
		free(result);
		result = NULL;
	}
	free(line);
	free(stash);
	return (result);
}

void	ft_free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	ft_insert(char **splitted, int *line, int row)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < row)
	{
		if (splitted[i][0] == '\n' || splitted[i] == NULL)
			j++;
		i++;
	}
	j = 0;
	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		line[j] = ft_atoi(splitted[i]);
		j++;
		i++;
	}
	line[j] = -1;
}

int	**ft_transform(char *str, int rows)
{
	int	**result;
	int	i;
	int	len;
	char	**splitted;

	i = 0;
	result = malloc(sizeof(int *) * (rows + 1));
	splitted = ft_split(str, ' ');
	while (splitted[i] && splitted[i][0] != '\n')
		i++;
	len = i + 1;
	free(str);
	i = 0;
	while (i < rows)
	{
		result[i] = malloc(sizeof(int) * len + 1);
		ft_insert(splitted, result[i], i);
		i++;
	}
	result[i] = NULL;
	ft_free_splitted(splitted);
	return (result);
}

void	ft_line_insert(char *line, char *result, int i, int j)
{
	while (line[i])
	{
		result[j] = line[i];
		if ((line[i + 1] == '\n' && line[i] != ' ') ||
			(line[i + 1] == '\0' && line[i] != ' '))
		{
			j++;
			result[j] = ' ';
		}
		j++;
		i++;
	}
	result[j] = '\0';
}
char	*ft_line_modify(char *line)
{
	char 	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i + 1] == '\n' && line[i] != ' ') ||
			(line[i + 1] == '\0' && line[i] != ' '))
			j++;
		i++;
	}
	result = malloc(ft_strlen(line) + 1 + j);
	ft_line_insert(line, result, 0, 0);
	free(line);
	return (result);
}

int	ft_iso_proj(int x, int y, int z)
{
	
}

// start at [50][50]
void	ft_coordinates(int	**grid)
{
	int	row;
	int	len;
	int	dist;

	row = 0;
	len = 0;
	while (grid[row])
		row++;
	while (grid[row - 1][len] != -1)
		len++;
	if (row > len)
		dist = 600 / row;
	else
		dist = 600 / len;
	len = 0;
	row = 0;
	while (grid[row])
	{
		while (grid[row][len])
		{
			grid[row][len] = ft_iso_proj(len, row, grid[row][len]);
			len++;
		}
		row++;
		len = 0;
	}
}

int	**ft_initialize(int fd)
{
	int	**grid;
	char	*line;
	char	*stash;
	int		i;

	i = -1;
	stash = NULL;
	grid = NULL;
	while (fd)
	{
		line = get_next_line(fd);
		if (line == NULL)
			fd = close(fd);
		if (line != NULL)
			stash = ft_join(stash, line);
		if (stash == NULL)
			return (NULL);
		i++;
	}
	stash = ft_line_modify(stash);
	grid = ft_transform(stash, i);
	// ft_coordinates(grid);
	return (grid);
}

int main(int argc, char **argv)
{
	// void *mlx;
	// t_data img;
	// void *mlx_window;
	int		fd;
	int		**grid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	// mlx = mlx_init();
	// mlx_window = mlx_new_window(mlx, 700, 700, "hi");
	// img.img = mlx_new_image(mlx, 700, 700);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	// &img.endian);
	grid = ft_initialize(fd);
	if (grid == NULL)
	{
		return (0);
		ft_printf("Map is not properly formatted");
	}
	while (grid[i] && grid[i][j] != -1)
	{
		if (grid[i][j + 1] == -1 && grid[i + 1])
		{
			printf("%d\n", grid[i][j]);
			i++;
			j = 0;
		}
		printf("%d", grid[i][j]);
		j++;
	}
	while (grid[i])
	{
		while (grid[i][j])
		{
			printf("%d", grid[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	free(grid);
	// mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	// mlx_loop(mlx);
}