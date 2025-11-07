/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:22 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**create_visited_map(int width, int height)
{
	char	**visited;
	int		i;

	visited = ft_calloc(height + 1, sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width + 1, sizeof(char));
		if (!visited[i])
		{
			free_visited_partial(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	check_accessible(char **map, char **visited, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_point	find_player(char **map)
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

void	flood_fill_helper(char **map, char **visited, t_flood_params p)
{
	if (p.x < 0 || p.x >= p.width || p.y < 0 || p.y >= p.height)
		return ;
	if (visited[p.y][p.x] || map[p.y][p.x] == '1')
		return ;
	visited[p.y][p.x] = 1;
	p.x++;
	flood_fill_helper(map, visited, p);
	p.x -= 2;
	flood_fill_helper(map, visited, p);
	p.x++;
	p.y++;
	flood_fill_helper(map, visited, p);
	p.y -= 2;
	flood_fill_helper(map, visited, p);
}

int	has_valid_path(char **map)
{
	t_point			player;
	char			**visited;
	t_flood_params	params;
	int				result;

	player = find_player(map);
	if (player.x == -1 || player.y == -1)
		return (0);
	params.height = 0;
	while (map[params.height])
		params.height++;
	params.width = ft_strlen(map[0]);
	visited = create_visited_map(params.width, params.height);
	if (!visited)
		return (0);
	params.x = player.x;
	params.y = player.y;
	flood_fill_helper(map, visited, params);
	result = check_accessible(map, visited, params.height);
	free_visited(visited);
	return (result);
}
