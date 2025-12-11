/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/11 17:13:49 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Frees a dynamically allocated 2D map array.
 *
 * Iterates through each row of the map and frees it, then frees the
 * array of pointers itself. Safely handles NULL maps by returning early.
 * This is the standard cleanup function for map grids loaded from files.
 * 
 * @param map A NULL-terminated 2D array of strings to free.
 */
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * @brief Frees a partially allocated visited array during pathfinding.
 *
 * Used for error handling during pathfinding when memory allocation fails
 * partway through creating the visited map. Frees only the rows that were
 * successfully allocated (from 0 to 'until'), then frees the array itself.
 * 
 * @param visited The partially allocated 2D array to free.
 * @param until The number of rows that were successfully allocated.
 */
void	free_visited_partial(char **visited, int until)
{
	while (until > 0)
		free(visited[--until]);
	free(visited);
}

/**
 * @brief Frees a complete visited array used in pathfinding.
 *
 * Deallocates a fully allocated visited map that was used during the
 * flood-fill pathfinding algorithm. Iterates through all rows and frees
 * them, then frees the array of pointers. Safely handles NULL arrays.
 * 
 * @param visited A NULL-terminated 2D array of characters to free.
 */
void	free_visited(char **visited)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

/**
 * @brief Performs complete game cleanup and exits the program.
 *
 * Deallocates all game resources in the proper order to prevent memory
 * leaks and ensure clean program termination:
 * 1. Destroys all texture images
 * 2. Destroys the game window
 * 3. Frees the map grid
 * 4. Destroys the MLX display connection
 * 5. Frees the MLX instance
 * 6. Exits the program with success code
 *
 * This function is called when the player closes the window or presses ESC.
 * 
 * @param game Pointer to the game structure containing all resources.
 *
 * @return Always returns 0, but the function calls exit() so this value
 *         is never actually returned.
 */
int	close_game(t_game *game)
{
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_map(game->map.grid);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
