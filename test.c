#include <mlx.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

unsigned int	ft_strlcpy_1(char *dest, char **s, unsigned int size)
{
	unsigned int	i;
	unsigned int	length;
	char *src;

	length = 0;
	src = *s;
	while (src[length] != '\0')
	{
		length++;
	}
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (size != 0)
		dest[i] = '\0';
	return (length);
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
	// while (splitted[i])
	// {
	// 	printf("%c\n", splitted[i][0]);
	// 	i++;
	// }
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


int main(void)
{
	char *p;
	char *p1;
	int	**p2;

	p1 = malloc(sizeof(char) * 17);
	p = "1 1 \n 2 2 \n 3 3 \0";
	ft_strlcpy_1(p1, &p, 17);
	p2 = ft_transform(p1, 3);
	int	i = 0;
	int	j = 0;
	while (p2[i])
	{
		while (p2[i][j] != -1)
		{
			printf("%d", p2[i][j]);
			j++;
		}
		printf("%d", p2[i][j]);
		i++;
		printf("\n");
		j = 0;
	}
	i = 0;
	while (p2[i])
	{
		free(p2[i]);
		i++;
	}
	free(p2);
}
