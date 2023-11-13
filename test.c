#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>

int main(void)
{
	char *c;

	c = "hi";
	int fd = open("t.fdf", O_RDONLY);
	while(c != NULL)
	{
		c = get_next_line(fd);
		printf("%s", c);
	}
	close(fd);
}
