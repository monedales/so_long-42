/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:27:30 by mona              #+#    #+#             */
/*   Updated: 2025/11/04 19:18:33 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static int	count_lines(int fd)
// {
// 	char	*line;
// 	int		count;

// 	count = 0;
// 	while ((line = get_next_line(fd)))
// 	{
// 		count++;
// 		free(line);
// 	}
// 	return (count);
// }


char	**read_map(const char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map");
		return (NULL);
	}
	map = NULL;
	count = 0;
	while ((line = get_next_line(fd)))
	{
		size_t len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		map = ft_append_line(map, line, count);
		if (!map)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		count++;
		free(line);
	}
	close(fd);
	return (map);
}

int	is_rectangular(char **map)
{
	int	len;
	int	i;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != (size_t)len)
			return (0);
		i++;
	}
	return (1);
}

int	has_only_valid_chars(char **map)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c == '\n')
				break;
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
int	has_closed_walls(char **map)
{
	int	i;
	int	j;
	int	width;
	int	height;

	if (!map || !map[0])
		return (0);
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	// validar primeira e última linha (todas devem ser '1')
	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	// validar colunas laterais (primeira e última coluna)
	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

