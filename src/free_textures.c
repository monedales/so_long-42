/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/11 17:13:49 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Frees all frames of the player idle animation.
 *
 * Helper function that destroys all 5 frames of the idle animation.
 * 
 * @param game Pointer to the game structure.
 */
static void	free_player_idle_animation(t_game *game)
{
	int	i;

	i = 0;
	while (i < IDLE_FRAMES)
	{
		if (game->player.back[i].img)
			mlx_destroy_image(game->mlx, game->player.back[i].img);
		i++;
	}
}

/**
 * @brief Frees all frames of the cheese animation.
 *
 * Helper function that destroys all 5 frames of the cheese animation.
 * 
 * @param game Pointer to the game structure.
 */
static void	free_cheese_animation(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->cheese[i].img)
			mlx_destroy_image(game->mlx, game->cheese[i].img);
		i++;
	}
}

static void	free_player_sprites(t_game *game)
{
	if (game->player.front.img)
		mlx_destroy_image(game->mlx, game->player.front.img);
	if (game->player.front_paw.img)
		mlx_destroy_image(game->mlx, game->player.front_paw.img);
	if (game->player.front_paw_mirror.img)
		mlx_destroy_image(game->mlx, game->player.front_paw_mirror.img);
	free_player_idle_animation(game);
	if (game->player.left.img)
		mlx_destroy_image(game->mlx, game->player.left.img);
	if (game->player.left_paw.img)
		mlx_destroy_image(game->mlx, game->player.left_paw.img);
	if (game->player.right.img)
		mlx_destroy_image(game->mlx, game->player.right.img);
	if (game->player.right_paw.img)
		mlx_destroy_image(game->mlx, game->player.right_paw.img);
	if (game->player.collect.img)
		mlx_destroy_image(game->mlx, game->player.collect.img);
}

/**
 * @brief Destroys all loaded texture images.
 *
 * Frees all MiniLibX image resources loaded during game initialization.
 * 
 * @param game Pointer to the game structure containing texture data.
 */
void	free_textures(t_game *game)
{
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->roof.img)
		mlx_destroy_image(game->mlx, game->roof.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->platform.img)
		mlx_destroy_image(game->mlx, game->platform.img);
	free_cheese_animation(game);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	free_player_sprites(game);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
}
