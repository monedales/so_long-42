/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/11/19 19:01:11 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_game *game, int x, int y, t_sprite *img)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - img->width) / 2;
	offset_y = (game->tile_size - img->height) / 2;
	draw_sprite_to_frame(&game->frame, img,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}

void	render_roof(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;

	offset_x = (game->tile_size - sprite->width) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size);
}

void	fill_floor_base(t_game *game, int x, int y)
{
	int		px;
	int		py;
	int		fill_color;

	fill_color = 0x654321;
	py = y * game->tile_size + game->floor.height;
	while (py < (y + 1) * game->tile_size)
	{
		px = x * game->tile_size;
		while (px < (x + 1) * game->tile_size)
		{
			put_pixel(&game->frame, px, py, fill_color);
			px++;
		}
		py++;
	}
}

void	render_sprite_centered(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - sprite->width) / 2;
	offset_y = (game->tile_size - sprite->height) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}
