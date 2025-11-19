/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 13:54:20 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_single_texture(t_game *game, t_sprite *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		handle_error(ERR_TEXTURE_FAILED);
		ft_printf("%s\n", path);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}

void	load_textures(t_game *game)
{
	load_single_texture(game, &game->wall, "assets/temp/wall.xpm");
	load_single_texture(game, &game->floor, "assets/temp/floor.xpm");
	load_single_texture(game, &game->platform,
		"so_long-sprites/platform.xpm");
	load_single_texture(game, &game->collectible,
		"assets/cheese/blue-cheese.xpm");
	load_single_texture(game, &game->exit, "assets/exit/exit-spaceship.xpm");
	load_single_texture(game, &game->player,
		"assets/sprites-louis/louis-front-grumpy.xpm");
}
