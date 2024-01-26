/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:00:01 by marvin            #+#    #+#             */
/*   Updated: 2023/02/17 12:45:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_getline(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = stash[i];
	if (stash[i] == '\n')
		line[i + 1] = '\0';
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	char	*buf;
	int		read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0 && ft_nl_check(stash) == 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*ft_left_stash(char *stash, char *line)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i)));
	if ((!new_stash) || (ft_strlen(stash) == ft_strlen(line)))
	{
		free(stash);
		if (new_stash)
			free(new_stash);
		return (NULL);
	}
	i++;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_getline(stash);
	stash = ft_left_stash(stash, line);
	return (line);
}

//int main(void)
//{
//	int fd = open("./test.txt", O_RDONLY);
//	char *p = get_next_line(fd);
//	printf("%s\n", p);
//	free(p);
//}
