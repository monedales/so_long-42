/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/19 18:50:09 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_visited_partial(char **visited, int until)
{
	while (until > 0)
		free(visited[--until]);
	free(visited);
}

void	free_visited(char **visited)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static void	free_textures(t_game *game)
{
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->roof.img)
		mlx_destroy_image(game->mlx, game->roof.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->platform.img)
		mlx_destroy_image(game->mlx, game->platform.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
}

int	close_game(t_game *game)
{
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_map(game->map.grid);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
