/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ozzy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/15 20:43:05 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Parses the map to find and initialize enemy positions.
 *
 * Iterates through the map grid to locate all enemies ('M') and stores
 * their positions in the enemies array. Sets initial direction to RIGHT
 * for all enemies.
 * 
 * This function must be called after enemy_count is determined and the
 * enemies array is allocated.
 * 
 * @param game Pointer to the game structure.
 */
void	parse_enemies(t_game *game)
{
	int	i;
	int	x;
	int	y;

	if (game->enemy_count == 0)
		return ;
	i = 0;
	y = 0;
	while (y < game->map.height && i < game->enemy_count)
	{
		x = 0;
		while (x < game->map.width && i < game->enemy_count)
		{
			if (game->map.grid[y][x] == 'M')
			{
				game->enemies[i].pos.x = x;
				game->enemies[i].pos.y = y;
				game->enemies[i].dir = DIR_RIGHT;
				game->map.grid[y][x] = '0';
				i++;
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Updates enemy movement (patrol behavior).
 *
 * Moves each enemy horizontally (left/right) and reverses direction
 * when hitting walls or obstacles. This function is called from the
 * main animation loop.
 * 
 * @param game Pointer to the game structure.
 */
void	update_enemies(t_game *game)
{
	int		i;
	int		new_x;
	char	tile;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].dir == DIR_RIGHT)
			new_x = game->enemies[i].pos.x + 1;
		else
			new_x = game->enemies[i].pos.x - 1;
		if (new_x < 0 || new_x >= game->map.width)
		{
			if (game->enemies[i].dir == DIR_RIGHT)
				game->enemies[i].dir = DIR_LEFT;
			else
				game->enemies[i].dir = DIR_RIGHT;
		}
		else
		{
			tile = game->map.grid[game->enemies[i].pos.y][new_x];
			if (tile == '1' || tile == 'F' || tile == 'G' || tile == 'R')
			{
				if (game->enemies[i].dir == DIR_RIGHT)
					game->enemies[i].dir = DIR_LEFT;
				else
					game->enemies[i].dir = DIR_RIGHT;
			}
			else
				game->enemies[i].pos.x = new_x;
		}
		if (check_enemy_collision(game))
		{
			close_game(game);
			exit(0);
		}
		i++;
	}
}

/**
 * @brief Checks collision between player and enemies.
 *
 * Compares player position with all enemy positions. If there's a
 * collision, triggers game over.
 * 
 * @param game Pointer to the game structure.
 * @return 1 if collision detected, 0 otherwise.
 */
int	check_enemy_collision(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->map.player_pos.x == game->enemies[i].pos.x
			&& game->map.player_pos.y == game->enemies[i].pos.y)
			return (1);
		i++;
	}
	return (0);
}
