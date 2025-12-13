/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/13 15:34:17 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Creates a 2D visited array for pathfinding tracking.
 *
 * Allocates a 2D array of the same dimensions as the map to track which
 * tiles have been visited during the flood-fill pathfinding algorithm.
 * All cells are initialized to 0 (unvisited) using ft_calloc.
 *
 * If allocation fails at any point, all previously allocated rows are
 * freed using free_visited_partial to prevent memory leaks.
 * 
 * @param width The width of the map (number of columns).
 * @param height The height of the map (number of rows).
 *
 * @return A NULL-terminated 2D array initialized to zeros on success,
 *         or NULL if memory allocation fails.
 */
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

/**
 * @brief Checks if all collectibles and the exit are reachable.
 *
 * Verifies that the flood-fill algorithm successfully reached all
 * essential game elements by checking the visited array. For the map
 * to be valid, every collectible ('C') and the exit ('E') must have
 * been marked as visited during pathfinding.
 * 
 * @param map The original map grid with game elements.
 * @param visited The visited array marking which tiles were reached.
 * @param height The height of the map (number of rows).
 *
 * @return 1 if all collectibles and exit are reachable (visited),
 *         0 if any collectible or exit remains unvisited.
 */
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

/**
 * @brief Finds the player's starting position in the map.
 *
 * Searches the entire map grid for the player character ('P') and
 * returns its coordinates. This position is used as the starting point
 * for the flood-fill pathfinding algorithm.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return A t_point structure containing the player's coordinates.
 *         Returns (-1, -1) if the player is not found (should not happen
 *         if map validation was performed correctly).
 */
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

/**
 * @brief Recursive flood-fill algorithm to mark reachable tiles.
 *
 * Performs a depth-first search starting from the given position to mark
 * all tiles reachable from that point. The algorithm:
 * 1. Checks boundaries and returns if out of bounds
 * 2. Returns if the tile is already visited or is a wall ('1')
 * 3. Marks the current tile as visited
 * 4. Recursively explores all 4 adjacent tiles (right, left, down, up)
 *
 * The flood-fill continues until all reachable tiles are explored.
 * Walls ('1') act as barriers that stop the flood from spreading.
 * 
 * @param map The original map grid (used to detect walls).
 * @param visited The visited tracking array (modified during recursion).
 * @param p A t_flood_params structure containing current position (x, y)
 *          and map dimensions (width, height).
 */
void	flood_fill_helper(char **map, char **visited, t_flood_params p)
{
	t_flood_params	next;

	if (p.x < 0 || p.x >= p.width || p.y < 0 || p.y >= p.height)
		return ;
	if (visited[p.y][p.x] || map[p.y][p.x] == '1')
		return ;
	if (map[p.y][p.x] == 'F' || map[p.y][p.x] == 'G' || map[p.y][p.x] == 'R')
		return ;
	visited[p.y][p.x] = 1;
	next = (t_flood_params){p.x + 1, p.y, p.width, p.height};
	flood_fill_helper(map, visited, next);
	next = (t_flood_params){p.x - 1, p.y, p.width, p.height};
	flood_fill_helper(map, visited, next);
	next = (t_flood_params){p.x, p.y + 1, p.width, p.height};
	flood_fill_helper(map, visited, next);
	next = (t_flood_params){p.x, p.y - 1, p.width, p.height};
	flood_fill_helper(map, visited, next);
}

/**
 * @brief Validates that a valid path exists to complete the game.
 *
 * Main pathfinding validation function that ensures the player can reach
 * all collectibles and the exit. The validation process:
 * 1. Finds the player's starting position
 * 2. Creates a visited tracking array
 * 3. Runs flood-fill algorithm from the player's position
 * 4. Checks if all collectibles ('C') and exit ('E') were reached
 * 5. Frees the visited array and returns the result
 *
 * This ensures the map is solvable before the game starts. A map without
 * a valid path would be impossible to complete.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 1 if a valid path exists to all collectibles and the exit,
 *         0 if the player cannot reach all required elements or if
 *         memory allocation fails.
 */
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
