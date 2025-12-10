/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/10 15:34:15 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Returns the appropriate player sprite based on current direction.
 *
 * Selects which player animation sprite to display based on the player's
 * current facing direction. When the player has been idle for IDLE_WAIT
 * iterations, the idle animation (tail wagging) plays regardless of direction.
 * Otherwise shows directional sprites:
 * - DIR_BACK: Player facing up/backwards
 * - DIR_LEFT: Player facing left
 * - DIR_RIGHT: Player facing right (currently uses same sprite as left)
 * - DIR_FRONT (default): Player facing down/forward
 * 
 * @param game Pointer to the game structure containing player animation data.
 *
 * @return Pointer to the t_sprite corresponding to the current direction.
 */
t_sprite	*get_player_sprite(t_game *game)
{
	if (game->player.anim_counter >= IDLE_WAIT)
		return (&game->player.back[game->player.frame]);
	else if (game->player.current_dir == DIR_BACK)
		return (&game->player.back[0]);
	else if (game->player.current_dir == DIR_LEFT)
		return (&game->player.left);
	else if (game->player.current_dir == DIR_RIGHT)
		return (&game->player.left);
	else
		return (&game->player.front);
}

/**
 * @brief Renders a tile sprite centered within its grid cell.
 *
 * Draws a sprite centered both horizontally and vertically within a tile
 * grid cell. Calculates the offset needed to center the sprite based on
 * the difference between the tile size (64x64) and the sprite dimensions.
 * This is used for tiles that should appear in the middle of their cell
 * (walls, floors, etc.).
 * 
 * @param game Pointer to the game structure containing frame buffer and tile size.
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 * @param img Pointer to the sprite to render.
 */
void	render_tile(t_game *game, int x, int y, t_sprite *img)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - img->width) / 2;
	offset_y = (game->tile_size - img->height) / 2;
	draw_sprite_to_frame(&game->frame, img,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}

/**
 * @brief Renders a sprite aligned to the top of its grid cell.
 *
 * Draws a sprite centered horizontally but aligned to the top edge of
 * its tile grid cell (y offset = 0). This is specifically designed for
 * roof/ceiling tiles that should hang from the top of the cell rather
 * than float in the middle, creating a proper side-view platformer effect.
 * 
 * @param game Pointer to the game structure containing frame buffer and tile size.
 * @param sprite Pointer to the sprite to render (typically a roof tile).
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 */
void	render_roof(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;

	offset_x = (game->tile_size - sprite->width) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size);
}

/**
 * @brief Renders a sprite centered within its grid cell with transparency.
 *
 * Draws a sprite centered both horizontally and vertically within a tile
 * grid cell. This function is used for game objects that need to be
 * displayed with transparency support (player, collectibles, exit, platforms).
 * The sprite is drawn using draw_sprite_to_frame which respects the
 * magenta (#FF00FF) transparency color key.
 * 
 * @param game Pointer to the game structure containing frame buffer and tile size.
 * @param sprite Pointer to the sprite to render.
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 */
void	render_sprite_centered(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - sprite->width) / 2;
	offset_y = (game->tile_size - sprite->height) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}
