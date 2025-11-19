/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 13:54:20 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_sprite_centered(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = (game->tile_size - sprite->width) / 2;
	offset_y = (game->tile_size - sprite->height) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}

static void	render_player_on_exit(t_game *game, int x, int y)
{
	if (x == game->map.player_pos.x && y == game->map.player_pos.y
		&& x == game->map.exit_pos.x && y == game->map.exit_pos.y)
	{
		render_sprite_centered(game, &game->exit, x, y);
		render_sprite_centered(game, &game->player, x, y);
	}
}

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

static void	render_cell(t_game *game, int x, int y)
{
	render_tile(game, x, y, &game->floor);
	if (game->map.grid[y][x] == '1')
		render_tile(game, x, y, &game->wall);
	if (game->map.grid[y][x] == 'F')
		render_sprite_centered(game, &game->platform, x, y);
	if (game->map.grid[y][x] == 'C')
		render_sprite_centered(game, &game->collectible, x, y);
	if (game->map.grid[y][x] == 'E')
		render_sprite_centered(game, &game->exit, x, y);
	if (game->map.grid[y][x] == 'P')
		render_sprite_centered(game, &game->player, x, y);
	render_player_on_exit(game, x, y);
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
			render_cell(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
