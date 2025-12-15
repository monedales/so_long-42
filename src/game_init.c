/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/15 12:45:32 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes the game window and frame buffer.
 *
 * Creates the MiniLibX window with dimensions based on the map size and
 * a fixed tile size of 64x64 pixels. Also initializes the frame buffer
 * image which is used for off-screen rendering before displaying to the
 * window. This double-buffering approach prevents flickering during
 * game updates.
 * 
 * @param game Pointer to the game structure containing map and MLX data.
 */
void	init_window(t_game *game)
{
	int	win_width;
	int	win_height;
	int	map_pixel_width;
	int	map_pixel_height;

	game->tile_size = 64;
	map_pixel_width = game->map.width * game->tile_size;
	map_pixel_height = game->map.height * game->tile_size;
	if (map_pixel_width > 800)
		win_width = 800;
	else
		win_width = map_pixel_width;
	if (map_pixel_height > 600)
		win_height = 600;
	else
		win_height = map_pixel_height;
	game->win = mlx_new_window(game->mlx, win_width, win_height,
			"So Long and thanx for all the cheese");
	if (!game->win)
		handle_error(ERR_NO_WIN);
	game->frame.img = mlx_new_image(game->mlx, win_width, win_height);
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = win_width;
	game->frame.height = win_height;
}

/**
 * @brief Calculates and stores the dimensions of the map.
 *
 * Parses the map grid to determine its width (number of columns) and
 * height (number of rows). The width is determined from the length of
 * the first row, and the height is counted by iterating through all rows.
 * These dimensions are stored in the game structure for later use in
 * rendering and collision detection.
 * 
 * @param game Pointer to the game structure containing the map grid.
 */
void	parse_map_dimensions(t_game *game)
{
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(game->map.grid[0]);
}

/**
 * @brief Parses a single tile and updates game state accordingly.
 *
 * Helper function that checks the character at position (x, y) in the
 * map and updates the game structure based on the tile type:
 * - 'P': Stores the player's starting position
 * - 'E': Stores the exit position
 * - 'C': Increments the collectibles counter
 * 
 * @param game Pointer to the game structure to update.
 * @param x The x-coordinate (column) of the tile to parse.
 * @param y The y-coordinate (row) of the tile to parse.
 */
static void	parse_tile(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'P')
	{
		game->map.player_pos.x = x;
		game->map.player_pos.y = y;
	}
	else if (game->map.grid[y][x] == 'E')
	{
		game->map.exit_pos.x = x;
		game->map.exit_pos.y = y;
	}
	else if (game->map.grid[y][x] == 'C')
		game->map.collectibles++;
}

/**
 * @brief Parses the map and initializes game state variables.
 *
 * Iterates through the entire map grid to:
 * - Count the total number of collectibles
 * - Find and store the player starting position
 * - Find and store the exit position
 * - Initialize game counters (moves, collected items)
 * - Initialize player animation state (direction and frame)
 *
 * This function must be called after parse_map_dimensions() and before
 * rendering begins.
 * 
 * @param game Pointer to the game structure to initialize.
 */
void	parse_map_data(t_game *game)
{
	int	x;
	int	y;

	game->map.collectibles = 0;
	game->map.collected = 0;
	game->moves = 0;
	game->enemy_count = 0;
	game->player.current_dir = DIR_FRONT;
	game->player.frame = 0;
	game->player.anim_counter = 0;
	game->player.is_collecting = 0;
	game->player.collect_counter = 0;
	game->player.walk_frame = 0;
	game->cheese_frame = 0;
	game->cheese_counter = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			parse_tile(game, x, y);
			if (game->map.grid[y][x] == 'M')
				game->enemy_count++;
			x++;
		}
		y++;
	}
}

/**
 * @brief Main initialization function for the game.
 *
 * Performs complete game initialization in the following order:
 * 1. Initializes the MiniLibX connection
 * 2. Parses map dimensions (width and height)
 * 3. Parses map data (player position, exit, collectibles count)
 * 4. Creates the game window and frame buffer
 * 5. Loads all texture sprites from files
 * 6. Renders the initial game state
 * 7. Sets up event hooks for window closing and keyboard input
 *
 * After this function completes, the game is ready to enter the
 * main event loop (mlx_loop).
 * 
 * @param game Pointer to the game structure to initialize. The map grid
 *             must already be loaded before calling this function.
 */
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error(ERR_NO_WIN);
	parse_map_dimensions(game);
	parse_map_data(game);
	init_window(game);
	init_camera(game);
	load_textures(game);
	init_enemies(game);
	parse_enemies(game);
	game->scene = 1;
	game->scene_id = 0;
	handle_scenes(game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, update_animation, game);
}
