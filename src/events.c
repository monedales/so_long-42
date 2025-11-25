/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/21 19:38:19 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static void	move_player(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->map.player_pos.x;
	old_y = game->map.player_pos.y;
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.collected++;
		game->map.grid[new_y][new_x] = '0';
	}
	if (game->map.grid[new_y][new_x] == 'E'
		&& game->map.collected == game->map.collectibles)
	{
		ft_printf("🎉 WEERK! You won! Moves: %d\n", game->moves + 1);
		close_game(game);
	}
	if (old_x == game->map.exit_pos.x && old_y == game->map.exit_pos.y)
		game->map.grid[old_y][old_x] = 'E';
	else
		game->map.grid[old_y][old_x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	game->moves++;
}

static void	process_movement(int keycode, int *new_x, int *new_y)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		(*new_y)--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		(*new_y)++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		(*new_x)--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		(*new_x)++;
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_pos.x;
	new_y = game->map.player_pos.y;
	if (keycode == KEY_ESC)
		close_game(game);
	process_movement(keycode, &new_x, &new_y);
	if (is_valid_move(game, new_x, new_y))
	{
		move_player(game, new_x, new_y);
		ft_printf("Moves: %d\n", game->moves);
		render_map(game);
	}
	return (0);
}

int	handle_close(t_game *game)
{
	close_game(game);
	return (0);
}
