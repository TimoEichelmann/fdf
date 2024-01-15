/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:16:13 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/09 17:23:19 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		line[i].z = -ft_atoi(splitted[i]);
		line[i].y = row;
		line[i].x = i;
		line[i].height = ft_atoi(splitted[i]);
		line[i].end = 1;
		i++;
	}
	line[i].end = 0;
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

void	ft_iso(t_point *p)
{
	double x;
	double	y;
	double	z;

	/*rotation around vertical axis*/
	x = cos(RAD) * p->x - sin(RAD) * p->y;
	y = sin(RAD) * p->x + cos(RAD) * p->y;
	p->x = x;
	/*rotation around horizontal axis*/
	y = cos(RAD2) * y - sin(RAD2) * p->z;
	z = sin(RAD2) * y + cos(RAD2) * p->z;
	p->z = z;
}

double	ft_round(double num)
{
	if (num - (int)num > 0.5)
		return ((int)num + 1);
	else
		return ((int)num);

}

void	ft_vectorize(t_point **grid, int row, int ll)
{
	int	len;
	int	height;
	double	total;

	if (grid[row][ll].z > grid[0][ll].x * 2)
		len = 400 / grid[row][ll].z;
	else
		len = 400 / (grid[0][ll].x * 2);
	height = grid[row][ll].z / 2 * len;
	printf("%f %f\n", grid[0][ll].x, grid[row][0].x);
	total = ft_pos((ft_pos(grid[0][ll].x * len) - ft_pos(grid[row][0].x * len)));
	printf("%f", total);
	row = 0;
	ll = 0;
	while (grid[row])
	{
		while (grid[row][ll].end)
		{
			grid[row][ll].x = ft_round((grid[row][ll].x * len) + 350 + total / 2);
			grid[row][ll].z = ft_round((grid[row][ll].z * len) - height + 350);
			grid[row][ll].y *= len;
			ll++;
		}
		row++;
		ll = 0;
	}
}

void	ft_coordinates(t_point	**grid)
{
	int	row;
	int	line;
	int	ll;

	row = 0;
	line = 0;
	while (grid[row])
	{
		while (grid[row][line].end)
		{
			ft_iso(&grid[row][line]);
			line++;
		}
		row++;
		ll = line;
		line = 0;
	}
	ft_vectorize(grid, row - 1, ll - 1);
}

void	ft_max_height(t_point **grid, int max)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			grid[i][j].max_height = max;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_gradient(t_point **grid)
{
	int	i;
	int	j;
	int	max_height;

	max_height = 0;
	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			if (max_height < grid[i][j].height)
				max_height = grid[i][j].height;
			j++;
		}
		j = 0;
		i++;
	}
	ft_max_height(grid, max_height);
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
	ft_gradient(grid);
	return (grid);
}

void	ft_free(t_point **grid, t_data *img, void *mlx, void *mlx_win)
{
	int	i;
	int	j;
	t_point *p;

	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			free(&grid[i][j]);
			j++;
		}
		free(&grid[i]);
		i++;
		j = 0;
	}
	mlx_destroy_image(mlx, img);
	mlx_clear_window(mlx, mlx_win);
	mlx_destroy_window (mlx, mlx_win);
}

void	ft_draw_grid(t_point **grid)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (grid[i])
	{
		while (grid[i][j].end)
		{
			if (grid[i][j + 1].end)
				ft_draw_line(&img, &grid[i][j], &grid[i][j + 1]);
			if (grid[i + 1])
				ft_draw_line(&img, &grid[i][j], &grid[i + 1][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_init_mlx(void *mlx, t_data *img, void *mlx_window)
{
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll,
	&img.endian);
	mlx_window = mlx_new_window(mlx, 700, 700, "hi");
	if ((!mlx) || (!mlx) || (!mlx_window))
		return (0);
	return (1);
}

int	ft_error_check(char **argv, int *fd)
{
	if (argc != 2)
	{
		printf("%s\n", "Wrong parameter specification. Use: ./fdf 'name of map file");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", "Given file couldn't be opened. Check acces rights.");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	void *mlx;
	t_data img;
	void *mlx_window;
	int		fd;
	t_point	**grid;

	if (!ft_error_check(argv, &fd))
		return (0);
	if (!ft_init_mlx(mlx, &img, mlx_window))
	{
		printf("%s\n", "Error with the initialization of the minilibx. Pls try again.");
		return (0);
	}
	grid = ft_initialize(fd);
	if (!grid)
	{
		printf("Map not properly formatted.");
		return (0);
	}
	ft_draw_grid(grid);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	//ft_free(grid, &img, mlx, mlx_window);
	mlx_loop(mlx);
}