/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/11/26 16:48:04 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	*get_player_sprite(t_game *game)
{
	if (game->player_dir == DIR_BACK)
		return (&game->player_back);
	else if (game->player_dir == DIR_LEFT)
		return (&game->player_left);
	else if (game->player_dir == DIR_RIGHT)
		return (&game->player_left);
	else
		return (&game->player_front);
}

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
