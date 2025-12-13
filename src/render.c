/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/11 17:46:06 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Renders the player sprite when standing on the exit.
 *
 * Special rendering case that handles layering when the player is standing
 * on the same tile as the exit. Draws the exit sprite first, then the
 * player sprite on top, ensuring the player is visible. This only triggers
 * when both the player and exit positions match the current cell being
 * rendered.
 * 
 * @param game Pointer to the game structure.
 * @param x The x-coordinate of the current cell being rendered.
 * @param y The y-coordinate of the current cell being rendered.
 */
static void	render_player_on_exit(t_game *game, int x, int y)
{
	t_sprite	*player_sprite;

	if (x == game->map.player_pos.x && y == game->map.player_pos.y
		&& x == game->map.exit_pos.x && y == game->map.exit_pos.y)
	{
		player_sprite = get_player_sprite(game);
		render_sprite_centered(game, &game->exit, x, y);
		render_sprite_centered(game, player_sprite, x, y);
	}
}

/**
 * @brief Renders a single map cell based on its character.
 *
 * Determines what to draw at position (x, y) in the map grid based on
 * the character at that position:
 * - '1': Wall tile (centered)
 * - 'R': Roof tile (top-aligned for side-view effect)
 * - 'G': Ground/floor tile (centered)
 * - 'F': Platform sprite (centered with transparency)
 * - 'C': Collectible sprite (centered with transparency)
 * - 'E': Exit sprite (centered with transparency)
 * - 'P': Player sprite (centered with transparency, direction-aware)
 *
 * Also handles the special case where the player is on the exit.
 * 
 * @param game Pointer to the game structure.
 * @param x The x-coordinate (column) in the map grid.
 * @param y The y-coordinate (row) in the map grid.
 */
static void	render_cell(t_game *game, int x, int y)
{
	t_sprite	*player_sprite;

	if (game->map.grid[y][x] == '1')
		render_tile(game, x, y, &game->wall);
	if (game->map.grid[y][x] == 'R')
		render_roof(game, &game->roof, x, y);
	if (game->map.grid[y][x] == 'G')
		render_tile(game, x, y, &game->floor);
	if (game->map.grid[y][x] == 'F')
		render_sprite_centered(game, &game->platform, x, y);
	if (game->map.grid[y][x] == 'C')
		render_sprite_centered(game, &game->cheese[game->cheese_frame], x, y);
	if (game->map.grid[y][x] == 'E')
		render_sprite_centered(game, &game->exit, x, y);
	if (game->map.grid[y][x] == 'P')
	{
		player_sprite = get_player_sprite(game);
		render_sprite_centered(game, player_sprite, x, y);
	}
	render_player_on_exit(game, x, y);
}

/**
 * @brief Renders a vertical gradient background.
 *
 * Fills the entire frame buffer with a smooth vertical gradient from
 * white at the top to light gray at the bottom. The gradient provides
 * a clean, atmospheric background for the game that doesn't interfere
 * with sprite visibility. Uses direct pixel manipulation for efficiency.
 * 
 * @param game Pointer to the game structure containing the frame buffer.
 */
static void	render_gradient_background(t_game *game)
{
	int		x;
	int		y;
	int		gray;
	int		color;
	char	*dst;

	y = 0;
	while (y < game->frame.height)
	{
		gray = 255 - (y * 55 / game->frame.height);
		color = (gray << 16) | (gray << 8) | gray;
		x = 0;
		while (x < game->frame.width)
		{
			dst = game->frame.addr + (y * game->frame.line_len
					+ x * (game->frame.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the move counter on screen.
 *
 * Displays the current move count in the top-left corner of the game
 * window using MiniLibX's text rendering. Creates a black outline effect
 * by drawing the text multiple times with slight offsets (creating shadow),
 * then drawing the main text in cyan/aqua color on top. This ensures
 * excellent readability against any background color.
 *
 * The outline is drawn in a 3x3 grid for better visibility.
 * Memory is properly managed by freeing the dynamically created strings.
 * 
 * @param game Pointer to the game structure containing move count and MLX data.
 */
static void	render_move_counter(t_game *game)
{
	char	*moves_str;
	char	*counter_text;
	int		i;
	int		j;

	moves_str = ft_itoa(game->moves);
	counter_text = ft_strjoin("Moves: ", moves_str);
	i = -2;
	while (++i < 3)
	{
		j = -2;
		while (++j < 3)
		{
			if (i != 0 || j != 0)
				mlx_string_put(game->mlx, game->win, 13 + i, 23 + j,
					0x000000, counter_text);
		}
	}
	mlx_string_put(game->mlx, game->win, 13, 23, 0xFFD700, counter_text);
	free(moves_str);
	free(counter_text);
}

/**
 * @brief Main rendering function that draws the complete game state.
 *
 * Orchestrates the entire rendering pipeline in the correct order:
 * 1. Renders gradient background to the frame buffer
 * 2. Iterates through every map cell and renders its contents
 * 3. Displays the completed frame buffer to the window
 * 4. Overlays the move counter text on top
 *
 * This function uses double-buffering: all drawing is done to an off-screen
 * frame buffer first, then the complete image is copied to the window in
 * one operation. This prevents flickering and tearing.
 *
 * Called initially during game setup and after every player movement.
 * 
 * @param game Pointer to the game structure containing all rendering data.
 */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	render_gradient_background(game);
	update_camera(game);
	y = game->camera.y;
	while (y < game->camera.y + game->camera.height
		&& y < game->map.height)
	{
		x = game->camera.x;
		while (x < game->camera.x + game->camera.width
			&& x < game->map.width)
		{
			render_cell(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	render_move_counter(game);
}
