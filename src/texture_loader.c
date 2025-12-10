/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/10 15:40:26 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Loads a single XPM texture file into a sprite structure.
 *
 * Helper function that loads an XPM image file using MiniLibX and stores
 * all necessary data in a t_sprite structure. The process:
 * 1. Loads the XPM file and stores the image pointer and dimensions
 * 2. If loading fails, prints an error message with the file path and exits
 * 3. Retrieves the image data address and pixel format information
 *
 * The image data address is needed for direct pixel manipulation during
 * rendering operations.
 * 
 * @param game Pointer to the game structure containing the MLX instance.
 * @param img Pointer to the sprite structure to populate with loaded data.
 * @param path The file path to the XPM image to load.
 */
static void	load_single_texture(t_game *game, t_sprite *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		handle_error(ERR_TEXTURE_FAILED);
		ft_printf("%s\n", path);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}

/**
 * @brief Loads idle animation frames for the player.
 *
 * Helper function that loads all frames of the idle animation (tail wagging).
 * Loads 5 frames from louis-back1.xpm through louis-back5.xpm into the
 * player.back array.
 *
 * This function was separated to make it easier to add more animations
 * in the future (walking, collecting, etc.).
 * 
 * @param game Pointer to the game structure.
 */
static void	load_player_idle_animation(t_game *game)
{
	load_single_texture(game, &game->player.back[0],
		"assets/sprites-louis/louis-back1.xpm");
	load_single_texture(game, &game->player.back[1],
		"assets/sprites-louis/louis-back2.xpm");
	load_single_texture(game, &game->player.back[2],
		"assets/sprites-louis/louis-back3.xpm");
	load_single_texture(game, &game->player.back[3],
		"assets/sprites-louis/louis-back4.xpm");
	load_single_texture(game, &game->player.back[4],
		"assets/sprites-louis/louis-back5.xpm");
}

/**
 * @brief Loads cheese animation frames.
 *
 * Helper function that loads all frames of the cheese animation.
 * Loads 5 different cheese types: blue cheese, brie, cheddar, gouda, parmesan.
 *
 * @param game Pointer to the game structure.
 */
static void	load_cheese_animation(t_game *game)
{
	load_single_texture(game, &game->cheese[0],
		"assets/cheese/blue-cheese.xpm");
	load_single_texture(game, &game->cheese[1],
		"assets/cheese/brie.xpm");
	load_single_texture(game, &game->cheese[2],
		"assets/cheese/cheddar.xpm");
	load_single_texture(game, &game->cheese[3],
		"assets/cheese/gouda.xpm");
	load_single_texture(game, &game->cheese[4],
		"assets/cheese/parmesan.xpm");
}

/**
 * @brief Loads all game textures from XPM files.
 *
 * Main texture loading function that loads all sprite assets needed for
 * the game. This includes:
 * - Environment tiles: wall, roof, floor, platform
 * - Game objects: collectible (cheese), exit (spaceship)
 * - Player animation sprites: front, back, left, collect
 *
 * Each texture is loaded using load_single_texture(), which handles error
 * checking and data retrieval. If any texture fails to load, the program
 * will exit with an error message indicating which file caused the problem.
 *
 * All sprites use the XPM format with magenta (#FF00FF) as the transparency
 * color key for proper alpha blending during rendering.
 *
 * This function must be called after MLX initialization and before any
 * rendering attempts.
 * 
 * @param game Pointer to the game structure where all textures will be stored.
 */
void	load_textures(t_game *game)
{
	load_single_texture(game, &game->wall, "assets/tiles/tile-wall-square.xpm");
	load_single_texture(game, &game->roof, "assets/tiles/tile-roof.xpm");
	load_single_texture(game, &game->floor, "assets/tiles/tile_floor.xpm");
	load_single_texture(game, &game->platform,
		"assets/tiles/platform.xpm");
	load_cheese_animation(game);
	load_single_texture(game, &game->exit, "assets/exit/exit-spaceship-80.xpm");
	load_single_texture(game, &game->player.front,
		"assets/sprites-louis/louis-front-grumpy.xpm");
	load_player_idle_animation(game);
	load_single_texture(game, &game->player.left,
		"assets/sprites-louis/louis-side-walk.xpm");
	load_single_texture(game, &game->player.collect,
		"assets/sprites-louis/louis-collect.xpm");
}
