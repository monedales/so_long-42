/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:15:48 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:00:38 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	game->tile_size = 64;
	win_width = game->map.width * game->tile_size;
	win_height = game->map.height * game->tile_size;
	game->win = mlx_new_window(game->mlx, win_width, win_height,
			"So Long and thanx for all the cheese");
	if (!game->win)
		handle_error(ERR_NO_WIN);
}

void	parse_map_dimensions(t_game *game)
{
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(game->map.grid[0]);
}

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

void	parse_map_data(t_game *game)
{
	int	x;
	int	y;

	game->map.collectibles = 0;
	game->map.collected = 0;
	game->moves = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			parse_tile(game, x, y);
			x++;
		}
		y++;
	}
}
