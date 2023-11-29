#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <math.h>

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
	int	z;
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

void	ft_insert(char **splitted, t_point *line, int row)
{
	int	i;

	i = 0;
	while (splitted[i] && splitted[i][0] != '\n')
	{
		line[i].z = ft_atoi(splitted[i]);
		line[i].y = row;
		line[i].x = i;
		i++;
	}
	line[i].x = -1;
}

t_point	**ft_transform(char *str, int rows)
{
	t_point	**result;
	int	i;
	int	len;
	char	**splitted;

	i = 0;
	result = malloc(sizeof(t_point *) * (rows + 1));
	splitted = ft_split(str, ' ');
	while (splitted[i] && splitted[i][0] != '\n')
		i++;
	len = i + 1;
	free(str);
	i = 0;
	while (i < rows)
	{
		result[i] = malloc(sizeof(t_point) * len + 1);
		ft_insert(splitted + (i * len), result[i], i);
		i++;
	}
	result[i] = NULL;
	ft_free_splitted(splitted);
	return (result);
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

void	ft_draw_line(t_data *img, t_point *p1, t_point *p2)
{
	char	*addr;

	if ((p1->x > p2->x) || (p1->x == p2->x && p1->y > p2->y))
		addr = img->addr + (((img->bpp / 8) * p2->x) + (img->ll * p2->y));
	else
		addr = img->addr + (((img->bpp / 8) * p1->x) + (img->ll * p1->y));

	if (p1->x != p2->x)
		ft_draw_angle_line(img, p1->x - p2->x, p1->y - p2->y, addr);
	else
		ft_draw_straight_line(img, p1->y - p2->y, addr);
}

void	ft_line_insert(char *line, char *result, int i, int j)
{
	while (line[i])
	{
		result[j] = line[i];
		if (line[i + 1] == '\0' && line[i] != ' ')
		{
			j++;
			result[j] = ' ';
		}
		if (line[i + 1] == '\n' && line[i] != ' ')
		{
			j = j + 3;
			result[j - 2] = ' ';
			result[j - 1] = '\n';
			result[j] = ' ';
			i++;
		}
		j++;
		i++;
	}
	result[j] = '\0';
}
char	*ft_line_modify(char *line)
{
	char 	*result;
	int		i;	// int		fd;
	// t_point	**grid;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i + 1] == '\n' && line[i] != ' ')
			j = j + 2;
		if (line[i + 1] == '\0' && line[i] != ' ')
			j++;
		i++;
	}
	result = malloc(ft_strlen(line) + 1 + j);
	ft_line_insert(line, result, 0, 0);
	free(line);
	return (result);
}

void	ft_vectorize(t_point *point, int dist, t_point start)
{
	point->x = point->x * 10;
	point->y = point->y * 10;
	point->z = point->z * 10;
}

void	ft_iso_proj(t_point *p)
{
	int	new_x;
	int	new_y;

	new_x = (p->x - p->y) * cos(0.8);
	new_y = (p->x + p->y) * sin(0.8) + p->z;
	p->x = new_x;
	p->y = new_y;
}

void	ft_coordinates(t_point	**grid)
{
	int	row;
	int	len;
	int	dist;

	row = 0;
	len = 0;
	while (grid[row])
		row++;
	while (grid[row - 1][len].x != -1)
		len++;
	if (row > len)
		dist = 600 / row;
	else
		dist = 600 / len;
	len = (700 - ((len - 1) * dist)) / 2;
	row = (700 - ((row - 1) * dist)) / 2;
	grid[0][0].x = len;
	grid[0][0].y = row;
	row = 0;
	len = 1;
	while (grid[row])
	{
		while (grid[row][len].x != -1)
		{
			ft_vectorize(&grid[row][len], dist, grid[0][0]);
			ft_iso_proj(&grid[row][len]);
			len++;
		}
		row++;
		len = 0;
	}
}

t_point **ft_initialize(int fd)
{
	t_point	**grid;
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
	ft_coordinates(grid);
	return (grid);
}

int main(int argc, char **argv)
{
	void *mlx;
	t_data img;
	void *mlx_window;
	int		fd;
	t_point	**grid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	&img.endian);
	mlx_window = mlx_new_window(mlx, 700, 700, "hi");
	grid = ft_initialize(fd);
	if (!grid)
	{
		printf("map not properly formatted");
		return (0);
	}
	// printf("p1 : (x : %d y : %d z = %d)\np2 : (x : %d y : %d z = %d)\n", grid[0][0].x,grid[0][0].y,grid[0][0].z,grid[0][1].x,grid[0][1].y,grid[0][1].z);
	// ft_draw_line(&img, &grid[0][0], &grid[0][1]);
	// ft_mlx_pxl_draw_pos(&img, grid[0][1].x, grid[0][1].y, 0x00FF0000);
	while (grid[i])
	{
		while (grid[i][j].x != -1)
		{
			if (grid[i][j + 1].x != -1)
				ft_draw_line(&img, &grid[i][j], &grid[i][j + 1]);
			if (grid[i + 1])
				ft_draw_line(&img, &grid[i][j], &grid[i + 1][j]);
			printf("x : %d y : %d z : %d\n", grid[i][j].x, grid[i][j].y, grid[i][j].z);
			j++;
		}
		printf("(x : %d)", grid[i][j].x);
		j = 0;
		i++;
		printf("\n");
	}
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}