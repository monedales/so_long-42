/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:39:32 by maria-ol         ###   ########.fr       */
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
