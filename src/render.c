/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 18:44:15 by mona             ###   ########.fr       */
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
	draw_sprite_to_frame(&game->frame, img,
		x * game->tile_size + offset_x,
		y * game->tile_size + offset_y);
}

static void	render_roof(t_game *game, t_sprite *sprite, int x, int y)
{
	int	offset_x;

	offset_x = (game->tile_size - sprite->width) / 2;
	draw_sprite_to_frame(&game->frame, sprite,
		x * game->tile_size + offset_x,
		y * game->tile_size);
}

// static void	render_floor(t_game *game, t_sprite *sprite, int x, int y)
// {
// 	int	offset_x;
// 	int	offset_y;

// 	offset_x = (game->tile_size - sprite->width) / 2;
// 	offset_y = game->tile_size - sprite->height;
// 	draw_sprite_to_frame(&game->frame, sprite,
// 		x * game->tile_size + offset_x,
// 		y * game->tile_size + offset_y);
// }

static void	fill_floor_base(t_game *game, int x, int y)
{
	int		px;
	int		py;
	int		fill_color;

	fill_color = 0x713A2E;
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

static void	render_cell(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		render_tile(game, x, y, &game->wall);
	if (game->map.grid[y][x] == 'R')
		render_roof(game, &game->roof, x, y);
	if (game->map.grid[y][x] == 'G')
	{
		fill_floor_base(game, x, y);
		render_roof(game, &game->floor, x, y);
	}
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

static void	render_gradient_background(t_game *game)
{
	int		x;
	int		y;
	int		gray;
	int		color;
	char	*dst;

	y = 0;
	while (y < game->frame.height)
	{
		gray = 255 - (y * 55 / game->frame.height);
		color = (gray << 16) | (gray << 8) | gray;
		x = 0;
		while (x < game->frame.width)
		{
			dst = game->frame.addr + (y * game->frame.line_len
					+ x * (game->frame.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	render_gradient_background(game);
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
