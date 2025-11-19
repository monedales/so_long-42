/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 19:01:11 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_player_on_exit(t_game *game, int x, int y)
{
	if (x == game->map.player_pos.x && y == game->map.player_pos.y
		&& x == game->map.exit_pos.x && y == game->map.exit_pos.y)
	{
		render_sprite_centered(game, &game->exit, x, y);
		render_sprite_centered(game, &game->player, x, y);
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
