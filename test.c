#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_point {
	int	x;
	int	y;
	int	z;
}t_point;

int main(void)
{
	t_point *p;

	p = malloc(sizeof(t_point) * 2);
	p[0] = 0;
}
