/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:29 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, int x, int y, t_sprite *img)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - img->width) / 2;
	offset_y = (game->tile_size - img->height) / 2;
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * game->tile_size
		+ offset_x, y * game->tile_size + offset_y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y, &game->floor);
			if (game->map.grid[y][x] == '1')
				render_tile(game, x, y, &game->wall);
			else if (game->map.grid[y][x] == 'C')
				render_tile(game, x, y, &game->collectible);
			else if (game->map.grid[y][x] == 'E')
				render_tile(game, x, y, &game->exit);
			else if (game->map.grid[y][x] == 'P')
				render_tile(game, x, y, &game->player);
			x++;
		}
		y++;
	}
}
