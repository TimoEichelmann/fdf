/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:05:31 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 19:13:18 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vars	*ft_vars(void *mlx, void *win, t_data *img)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->mlx = mlx;
	vars->win = win;
	vars->img = img;
	return (vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 0xff1b)
	{
		mlx_destroy_image(vars->mlx, vars->img->img);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free(vars);
		exit (0);
	}
	return (0);
}

int	ft_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars);
	exit (0);
}

void	ft_events(void *mlx, void *win, t_data *img)
{
	t_vars	*vars;

	vars = ft_vars(mlx, win, img);
	mlx_key_hook(win, key_hook, vars);
	mlx_hook(win, 17, 0, ft_exit, vars);
}
