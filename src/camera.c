/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/11 18:04:38 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes the camera viewport system.
 *
 * Sets up the camera dimensions and maximum bounds based on window size
 * and map dimensions. The camera shows a portion of the map centered on
 * the player, handling edge cases when near map borders.
 * 
 * @param game Pointer to the game structure.
 */
void	init_camera(t_game *game)
{
	game->camera.width = game->frame.width / game->tile_size;
	game->camera.height = game->frame.height / game->tile_size;
	game->camera.max_x = game->map.width - game->camera.width;
	game->camera.max_y = game->map.height - game->camera.height;
	if (game->camera.max_x < 0)
		game->camera.max_x = 0;
	if (game->camera.max_y < 0)
		game->camera.max_y = 0;
	game->camera.x = 0;
	game->camera.y = 0;
}

/**
 * @brief Updates camera position to center on player.
 *
 * Calculates the camera position to keep the player centered in the
 * viewport. Clamps camera position to map boundaries to prevent showing
 * areas outside the map.
 * 
 * @param game Pointer to the game structure.
 */
void	update_camera(t_game *game)
{
	int	target_x;
	int	target_y;

	target_x = game->map.player_pos.x - (game->camera.width / 2);
	target_y = game->map.player_pos.y - (game->camera.height / 2);
	if (target_x < 0)
		target_x = 0;
	if (target_y < 0)
		target_y = 0;
	if (target_x > game->camera.max_x)
		target_x = game->camera.max_x;
	if (target_y > game->camera.max_y)
		target_y = game->camera.max_y;
	game->camera.x = target_x;
	game->camera.y = target_y;
}
