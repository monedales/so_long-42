/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:15:48 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 17:05:04 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	game->tile_size = 32;
	win_width = game->map.width * game->tile_size;
	win_height = game->map.height * game->tile_size;
	game->win = mlx_new_window(game->mlx, win_width, win_height,
			"So Long and thanx for all the cheese - Louis vs Ozzy");
	if (!game->win)
		handle_error(ERR_NO_WIN);
}

void	init_map(t_game *game, char *filepath)
{
	game->map.grid = read_map(filepath);
	if (!game->map.grid)
		handle_error(ERR_MAP_FAILED);
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(game->map.grid[0]);

	parse_map_data(game);
}
