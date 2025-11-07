/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 19:24:27 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_single_texture(t_game *game, t_sprite *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		exit(1);
	}
}

void	load_textures(t_game *game)
{
	load_single_texture(game, &game->wall, "assets/temp/wall.xpm");
	load_single_texture(game, &game->floor, "assets/temp/floor.xpm");
	load_single_texture(game, &game->collectible, "assets/temp/cheese.xpm");
	load_single_texture(game, &game->exit, "assets/temp/exit.xpm");
	load_single_texture(game, &game->player,
		"assets/sprites-louis/louis-front.xpm");
}

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
