/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/09 16:11:24 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Counts occurrences of player, exit, and collectible characters.
 *
 * Helper function that increments the appropriate counter based on the
 * character type. Used during map validation to track the number of
 * essential game elements.
 * 
 * @param c The character to check ('P', 'E', or 'C').
 * @param p Pointer to player count, incremented if c == 'P'.
 * @param e Pointer to exit count, incremented if c == 'E'.
 * @param coll Pointer to collectible count, incremented if c == 'C'.
 */
static void	count_elements(char c, int *p, int *e, int *coll)
{
	if (c == 'P')
		(*p)++;
	else if (c == 'E')
		(*e)++;
	else if (c == 'C')
		(*coll)++;
}

/**
 * @brief Validates that the map has the correct number of game elements.
 *
 * Iterates through the entire map and counts the occurrences of essential
 * game elements. For a valid so_long map, the requirements are:
 * - Exactly 1 player starting position ('P')
 * - Exactly 1 exit ('E')
 * - At least 1 collectible ('C')
 *
 * Having more or fewer than these exact counts makes the map invalid and
 * unplayable according to the game rules.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 1 if the map has exactly 1 player, 1 exit, and at least 1 collectible,
 *         0 otherwise.
 */
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
			count_elements(map[i][j], &p_count, &e_count, &c_count);
			j++;
		}
		i++;
	}
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}
