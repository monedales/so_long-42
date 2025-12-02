/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/26 16:48:04 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_player_on_exit(t_game *game, int x, int y)
{
	t_sprite	*player_sprite;

	if (x == game->map.player_pos.x && y == game->map.player_pos.y
		&& x == game->map.exit_pos.x && y == game->map.exit_pos.y)
	{
		player_sprite = get_player_sprite(game);
		render_sprite_centered(game, &game->exit, x, y);
		render_sprite_centered(game, player_sprite, x, y);
	}
}

static void	render_cell(t_game *game, int x, int y)
{
	t_sprite	*player_sprite;

	if (game->map.grid[y][x] == '1')
		render_tile(game, x, y, &game->wall);
	if (game->map.grid[y][x] == 'R')
		render_roof(game, &game->roof, x, y);
	if (game->map.grid[y][x] == 'G')
		render_tile(game, x, y, &game->floor);
	if (game->map.grid[y][x] == 'F')
		render_sprite_centered(game, &game->platform, x, y);
	if (game->map.grid[y][x] == 'C')
		render_sprite_centered(game, &game->collectible, x, y);
	if (game->map.grid[y][x] == 'E')
		render_sprite_centered(game, &game->exit, x, y);
	if (game->map.grid[y][x] == 'P')
	{
		player_sprite = get_player_sprite(game);
		render_sprite_centered(game, player_sprite, x, y);
	}
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

static void	render_move_counter(t_game *game)
{
	char	*moves_str;
	char	*counter_text;
	int		i;
	int		j;

	moves_str = ft_itoa(game->moves);
	counter_text = ft_strjoin("Moves: ", moves_str);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
			mlx_string_put(game->mlx, game->win, 18 + i, 28 + j,
				0x000000, counter_text);
	}
	mlx_string_put(game->mlx, game->win, 18, 28, 0xFFFFFF, counter_text);
	free(moves_str);
	free(counter_text);
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
	render_move_counter(game);
}
