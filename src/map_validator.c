/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/02 20:52:33 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Validates that the top and bottom rows are completely walled.
 *
 * Checks that every position in the first row (top) and last row (bottom)
 * of the map contains a wall character ('1'). This ensures the map is
 * properly enclosed horizontally.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 * @param width The width of the map (number of columns).
 * @param height The height of the map (number of rows).
 *
 * @return 1 if both top and bottom rows are completely walled,
 *         0 if any position is not a wall.
 */
static int	check_horizontal_walls(char **map, int width, int height)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

/**
 * @brief Validates that the left and right columns are completely walled.
 *
 * Checks that the first column (leftmost) and last column (rightmost)
 * of every row in the map contains a wall character ('1'). This ensures
 * the map is properly enclosed vertically. Skips the first and last rows
 * as they are already validated by check_horizontal_walls.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 * @param width The width of the map (number of columns).
 * @param height The height of the map (number of rows).
 *
 * @return 1 if both left and right columns are completely walled,
 *         0 if any position is not a wall.
 */
static int	check_vertical_walls(char **map, int width, int height)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates that the map is completely surrounded by walls.
 *
 * Ensures the entire perimeter of the map consists of wall characters ('1').
 * This prevents the player from moving outside the game boundaries.
 * Combines horizontal wall checking (top and bottom rows) with vertical
 * wall checking (left and right columns).
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 1 if the map is completely enclosed by walls,
 *         0 if the map is NULL, empty, or has any open edges.
 */
int	has_closed_walls(char **map)
{
	int	width;
	int	height;

	if (!map || !map[0])
		return (0);
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	if (!check_horizontal_walls(map, width, height))
		return (0);
	if (!check_vertical_walls(map, width, height))
		return (0);
	return (1);
}

/**
 * @brief Performs comprehensive validation of the game map.
 *
 * Executes a series of validation checks to ensure the map meets all
 * requirements for the so_long game. Validation steps include:
 * 1. Map is rectangular (all rows have equal length)
 * 2. Only valid characters are present (0, 1, C, E, P, F, G, R)
 * 3. Map is completely surrounded by walls ('1')
 * 4. Correct number of elements (1 player, 1 exit, at least 1 collectible)
 * 5. Valid path exists from player to all collectibles and the exit
 *
 * Validation stops at the first error encountered and returns the
 * corresponding error code.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 0 if the map is valid and playable,
 *         or a specific error code from t_error enum:
 *         - ERR_NOT_RECTANG: Map is not rectangular
 *         - ERR_CHARS_INVALID: Invalid characters found
 *         - ERR_NOT_WALLS: Map is not surrounded by walls
 *         - ERR_ELEM_INVALID: Wrong number of players, exits, or collectibles
 *         - ERR_NO_PATH: No valid path to complete the game
 */
int	validate_map(char **map)
{
	if (!is_rectangular(map))
		return (ERR_NOT_RECTANG);
	if (!has_only_valid_chars(map))
		return (ERR_CHARS_INVALID);
	if (!has_closed_walls(map))
		return (ERR_NOT_WALLS);
	if (!has_valid_counts(map))
		return (ERR_ELEM_INVALID);
	if (!has_valid_path(map))
		return (ERR_NO_PATH);
	return (0);
}
