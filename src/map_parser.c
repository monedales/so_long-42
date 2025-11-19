/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 13:54:20 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	**handle_read_error(char *line, int fd)
{
	free(line);
	close(fd);
	return (NULL);
}

char	**read_map(const char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		map = ft_append_line(map, line, count);
		if (!map)
			return (handle_read_error(line, fd));
		count++;
		free(line);
		line = get_next_line(fd);
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
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c == '\n')
				break ;
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P'
				&& c != 'F')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
