/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:16:13 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 19:43:50 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(t_point **grid)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
		j = 0;
	}
	free(grid);
}

int	ft_init_mlx(void **mlx, t_data *img, void **mlx_window)
{
	*mlx = mlx_init();
	img->img = mlx_new_image(*mlx, 700, 700);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll,
			&img->endian);
	*mlx_window = mlx_new_window(*mlx, 700, 700, "hi");
	if ((!mlx) || (!img) || (!mlx_window))
		return (0);
	return (1);
}

int	ft_error_check(char **argv, int *fd, int argc)
{
	if (argc != 2)
	{
		ft_printf("Wrong parameter. Use: ./fdf 'name of map file'\n");
		return (0);
	}
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
	{
		ft_printf("Given file couldn't be opened. Check acces rights.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	t_data	img;
	void	*mlx_window;
	int		fd;
	t_point	**grid;

	if (!ft_error_check(argv, &fd, argc))
		return (0);
	grid = ft_initialize(fd);
	if (!grid)
	{
		ft_printf("Map not properly formatted.\n");
		return (0);
	}
	if (!ft_init_mlx(&mlx, &img, &mlx_window))
	{
		ft_printf("Error with the initialization of the minilibx.\n");
		return (0);
	}
	ft_draw_grid(&img, grid);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	ft_free(grid);
	ft_events(mlx, mlx_window, &img);
	mlx_loop(mlx);
}
