/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/10 19:51:15 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Validates if a move to the specified position is allowed.
 *
 * Checks multiple conditions to determine if the player can move to
 * position (new_x, new_y):
 * - Position is within map boundaries
 * - Target tile is not a wall ('1')
 * - Target tile is not a platform ('F')
 * - Target tile is not ground/floor ('G')
 * - Target tile is not a roof ('R')
 *
 * Empty spaces ('0'), collectibles ('C'), exits ('E'), and the player
 * starting position ('P') are all valid movement targets.
 * 
 * @param game Pointer to the game structure containing the map.
 * @param new_x The target x-coordinate (column).
 * @param new_y The target y-coordinate (row).
 *
 * @return 1 if the move is valid, 0 if blocked or out of bounds.
 */
static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map.width)
		return (0);
	if (new_y < 0 || new_y >= game->map.height)
		return (0);
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'F')
		return (0);
	if (game->map.grid[new_y][new_x] == 'G')
		return (0);
	if (game->map.grid[new_y][new_x] == 'R')
		return (0);
	return (1);
}

/**
 * @brief Updates the map grid after player movement.
 * 
 * @param game Pointer to the game structure.
 * @param new_x New x-coordinate.
 * @param new_y New y-coordinate.
 */
static void	update_map_grid(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->map.player_pos.x;
	old_y = game->map.player_pos.y;
	if (old_x == game->map.exit_pos.x && old_y == game->map.exit_pos.y)
		game->map.grid[old_y][old_x] = 'E';
	else
		game->map.grid[old_y][old_x] = '0';
	game->map.grid[new_y][new_x] = 'P';
}

/**
 * @brief Executes a player movement to a new position.
 *
 * Performs the following actions when moving the player:
 * 1. Stores the current player position
 * 2. Checks if the target tile is a collectible ('C') and increments
 *    the collected counter if so
 * 3. Checks win condition: if moving onto exit ('E') with all collectibles
 *    collected, displays victory message and closes the game
 * 4. Updates the map grid: restores exit tile if leaving it, otherwise
 *    clears the old position
 * 5. Updates player position in both the map grid and game structure
 * 6. Increments the move counter
 *
 * This function assumes the move has already been validated.
 * 
 * @param game Pointer to the game structure.
 * @param new_x The target x-coordinate (column) to move to.
 * @param new_y The target y-coordinate (row) to move to.
 */
static void	move_player(t_game *game, int new_x, int new_y)
{
	game->player.is_collecting = 0;
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.collected++;
		game->player.is_collecting = 1;
		game->map.grid[new_y][new_x] = '0';
	}
	if (game->map.grid[new_y][new_x] == 'E'
		&& game->map.collected == game->map.collectibles)
	{
		ft_printf("🎉 WEERK! You won! Moves: %d\n", game->moves + 1);
		close_game(game);
	}
	update_map_grid(game, new_x, new_y);
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	game->moves++;
	game->player.walk_frame++;
}

/**
 * @brief Processes keyboard input and updates movement coordinates.
 *
 * Translates keyboard input into movement direction and updates the
 * player's animation direction. Supports both WASD and arrow keys:
 * - W/Up Arrow: Move up (decrease y), face backwards
 * - S/Down Arrow: Move down (increase y), face forward
 * - A/Left Arrow: Move left (decrease x), face left
 * - D/Right Arrow: Move right (increase x), face right
 *
 * The function modifies the new_x and new_y coordinates by reference
 * and updates the player's current direction for sprite animation.
 * 
 * @param keycode The keyboard key code from MiniLibX event.
 * @param new_x Pointer to the new x-coordinate to modify.
 * @param new_y Pointer to the new y-coordinate to modify.
 * @param game Pointer to the game structure to update player direction.
 */
static void	process_movement(int keycode, int *new_x, int *new_y, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		(*new_y)--;
		game->player.current_dir = DIR_BACK;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		(*new_y)++;
		game->player.current_dir = DIR_FRONT;
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		(*new_x)--;
		game->player.current_dir = DIR_LEFT;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		(*new_x)++;
		game->player.current_dir = DIR_RIGHT;
	}
}

/**
 * @brief Handles all keyboard input events for the game.
 *
 * Main keyboard event handler that processes player input and triggers
 * appropriate game actions:
 * - ESC key: Immediately closes the game
 * - Movement keys (WASD/Arrows): Attempts to move the player
 *
 * For movement keys, the function:
 * 1. Calculates the target position based on current position and key pressed
 * 2. Updates the player's facing direction for sprite animation
 * 3. Validates the move using collision detection
 * 4. If valid, executes the move, prints move count, and re-renders the map
 *
 * This function is registered as a key hook in MiniLibX and is called
 * automatically on every key press.
 * 
 * @param keycode The keyboard key code from the MiniLibX event system.
 * @param game Pointer to the game structure containing all game state.
 *
 * @return Always returns 0 (required by MiniLibX hook system).
 */
int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_pos.x;
	new_y = game->map.player_pos.y;
	if (keycode == KEY_ESC)
		close_game(game);
	process_movement(keycode, &new_x, &new_y, game);
	if (new_x != game->map.player_pos.x || new_y != game->map.player_pos.y)
	{
		game->player.anim_counter = 0;
		game->player.frame = 0;
	}
	if (is_valid_move(game, new_x, new_y))
	{
		move_player(game, new_x, new_y);
		ft_printf("Moves: %d\n", game->moves);
		render_map(game);
	}
	return (0);
}
