/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/07 17:06:04 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, int x, int y, t_sprite *img)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - img->width) / 2;
	offset_y = (game->tile_size - img->height) / 2;
	draw_sprite_opaque(&game->frame, img,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
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
			{
				draw_sprite_to_frame(&game->frame, &game->collectible,
					x * game->tile_size + (game->tile_size - game->collectible.width) / 2,
					y * game->tile_size + (game->tile_size - game->collectible.height) / 2);
			}
			else if (game->map.grid[y][x] == 'E')
			{
				draw_sprite_to_frame(&game->frame, &game->exit,
					x * game->tile_size + (game->tile_size - game->exit.width) / 2,
					y * game->tile_size + (game->tile_size - game->exit.height) / 2);
			}
			else if (game->map.grid[y][x] == 'P')
			{
				draw_sprite_to_frame(&game->frame, &game->player,
					x * game->tile_size + (game->tile_size - game->player.width) / 2,
					y * game->tile_size + (game->tile_size - game->player.height) / 2);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
