#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#define RAD 0.785398
#define RAD2  0.615473

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
}t_point;


void	ft_rotate_vertical(t_point *p)
{
	double x;
	double	y;

	x = cos(RAD) * p->x - sin(RAD) * p->y;
	y = sin(RAD) * p->x + cos(RAD) * p->y;
	p->x = x;
	p->y = y;
}

void	ft_rotate_horizontal(t_point *p)
{
	double	y;
	double	z;

	y = cos(RAD2) * p->y - sin(RAD2) * p->z;
	z = sin(RAD2) * p->y + cos(RAD2) * p->z;
	p->y = y;
	p->z = z;
}

int main(void)
{
	t_point p;

	p.x = 2;
	p.y = 0;
	p.z = 0;
	ft_rotate_vertical(&p);
	ft_rotate_horizontal(&p);
	printf("%f,%f,%f\n", p.x, p.y, p.z);
}

