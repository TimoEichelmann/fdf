/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:13:17 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/09 17:21:34 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#define RAD 0.785398
#define RAD2  0.615473

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}t_data;

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
	double	height;
	double	max_height;
	int		end;
}t_point;

int		ft_pos(int	num);
void	ft_plot(t_point *plot, t_point *p1, char ind);
void	ft_draw_high_line(t_data *img, t_point *p1, t_point *p2);
void	ft_draw_low_line(t_data *img, t_point *p1, t_point *p2);
void	ft_draw_line(t_data *img, t_point *p1, t_point *p2);
void	ft_mlx_pxl_draw_pos(t_data *img, int x, int y, int color);
void	ft_mlx_pxl_draw_addr(t_data *img, char *addr, int color);
char	*ft_join(char *stash, char *line);
void	ft_free_splitted(char **splitted);
void	ft_insert(char **splitted, t_point *line, int row);
t_point	**ft_transform(char *str, int rows);
void	ft_line_insert(char *line, char *result, int i, int j);
char	*ft_line_modify(char *line);
void	ft_iso(t_point *p);
double	ft_round(double num);
void	ft_vectorize(t_point **grid, int row, int ll);
void	ft_coordinates(t_point	**grid);
t_point **ft_initialize(int fd);
int		ft_pos(int	num);

#endif