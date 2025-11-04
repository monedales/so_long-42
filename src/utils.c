/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:17:46 by mona              #+#    #+#             */
/*   Updated: 2025/11/04 20:01:27 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_ber_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}

char	**ft_append_line(char **map, char *line, int count)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(count + 2, sizeof(char *)); // +1 pra nova linha, +1 pra NULL
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[count] = ft_strdup(line); // duplica a linha
	if (!new_map[count])
		return (NULL);
	free(map); // libera o array antigo
	return (new_map);
}

int	has_valid_counts(char **map)
{
	int	i;
	int	j;
	int	p_count;
	int	e_count;
	int	c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				p_count++;
			else if (map[i][j] == 'E')
				e_count++;
			else if (map[i][j] == 'C')
				c_count++;
			j++;
		}
		i++;
	}
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}

static void	flood_fill(char **map, char **visited, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	if (visited[y][x] || map[y][x] == '1')
		return;
	visited[y][x] = 1;
	flood_fill(map, visited, x + 1, y, width, height);
	flood_fill(map, visited, x - 1, y, width, height);
	flood_fill(map, visited, x, y + 1, width, height);
	flood_fill(map, visited, x, y - 1, width, height);
}

static t_point	find_player(char **map)
{
	t_point	pos;
	int		i;
	int		j;

	pos.x = -1;
	pos.y = -1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

static char	**create_visited_map(int width, int height)
{
	char	**visited;
	int		i;
	int		j;

	visited = ft_calloc(height + 1, sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width + 1, sizeof(char));
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j < width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

static void	free_visited(char **visited)
{
	int	i;

	if (!visited)
		return;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	has_valid_path(char **map)
{
	t_point	player;
	char	**visited;
	int		width;
	int		height;
	int		i;
	int		j;

	player = find_player(map);
	if (player.x == -1 || player.y == -1)
		return (0);
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	visited = create_visited_map(width, height);
	if (!visited)
		return (0);
	flood_fill(map, visited, player.x, player.y, width, height);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i][j])
			{
				free_visited(visited);
				return (0);
			}
			j++;
		}
		i++;
	}
	free_visited(visited);
	return (1);
}
