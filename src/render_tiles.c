/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/11 17:46:06 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_sprite	*get_lateral_sprite(t_game *game, int is_right)
{
	if (is_right)
	{
		if (game->player.walk_frame % 2 == 0)
			return (&game->player.right);
		else
			return (&game->player.right_paw);
	}
	else
	{
		if (game->player.walk_frame % 2 == 0)
			return (&game->player.left);
		else
			return (&game->player.left_paw);
	}
}

/**
 * @brief Returns the appropriate player sprite based on current direction.
 *
 * Selects which player animation sprite to display based on the player's
 * current facing direction. When the player has been idle for IDLE_WAIT
 * iterations, the idle animation (tail wagging) plays regardless of direction.
 * 
 * @param game Pointer to the game structure containing player animation data.
 *
 * @return Pointer to the t_sprite corresponding to the current direction.
 */
t_sprite	*get_player_sprite(t_game *game)
{
	if (game->player.is_collecting)
		return (&game->player.collect);
	if (game->player.anim_counter >= IDLE_WAIT)
		return (&game->player.back[game->player.frame]);
	if (game->player.current_dir == DIR_BACK)
		return (&game->player.back[game->player.frame]);
	if (game->player.current_dir == DIR_LEFT)
		return (get_lateral_sprite(game, 0));
	if (game->player.current_dir == DIR_RIGHT)
		return (get_lateral_sprite(game, 1));
	if (game->moves == 0)
		return (&game->player.front);
	if (game->player.walk_frame % 2 == 0)
		return (&game->player.front_paw);
	return (&game->player.front_paw_mirror);
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
 * @param game Pointer to the game struct containing frame buffer and tile size.
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 * @param img Pointer to the sprite to render.
 */
void	render_tile(t_game *game, int x, int y, t_sprite *img)
{
	int	offset_x;
	int	offset_y;
	int	screen_x;
	int	screen_y;

	offset_x = (game->tile_size - img->width) / 2;
	offset_y = (game->tile_size - img->height) / 2;
	screen_x = (x - game->camera.x) * game->tile_size + offset_x;
	screen_y = (y - game->camera.y) * game->tile_size + offset_y;
	draw_sprite_to_frame(&game->frame, img, screen_x, screen_y);
}

/**
 * @brief Renders a sprite aligned to the top of its grid cell.
 *
 * Draws a sprite centered horizontally but aligned to the top edge of
 * its tile grid cell (y offset = 0). This is specifically designed for
 * roof/ceiling tiles that should hang from the top of the cell rather
 * than float in the middle, creating a proper side-view platformer effect.
 * 
 * @param game Pointer to the game struct containing frame buffer and tile size.
 * @param sprite Pointer to the sprite to render (typically a roof tile).
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 */
void	render_roof(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;
	int	screen_x;
	int	screen_y;

	offset_x = (game->tile_size - sprite->width) / 2;
	screen_x = (x - game->camera.x) * game->tile_size + offset_x;
	screen_y = (y - game->camera.y) * game->tile_size;
	draw_sprite_to_frame(&game->frame, sprite, screen_x, screen_y);
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
 * @param game Pointer to the game struct containing frame buffer and tile size.
 * @param sprite Pointer to the sprite to render.
 * @param x The x-coordinate (column) in the grid (not pixels).
 * @param y The y-coordinate (row) in the grid (not pixels).
 */
void	render_sprite_centered(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;
	int	offset_y;
	int	screen_x;
	int	screen_y;

	offset_x = (game->tile_size - sprite->width) / 2;
	offset_y = (game->tile_size - sprite->height) / 2;
	screen_x = (x - game->camera.x) * game->tile_size + offset_x;
	screen_y = (y - game->camera.y) * game->tile_size + offset_y;
	draw_sprite_to_frame(&game->frame, sprite, screen_x, screen_y);
}
