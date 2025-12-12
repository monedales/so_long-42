/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/12 15:37:36 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Handles the cutscene sequence progression.
 * 
 * Controls which scene to display based on scene_id and advances
 * the story. Scene IDs:
 * - 0-1: Intro cutscenes
 * - 2: Start game (disable cutscene mode)
 * - 10: Error - tried to exit without all collectibles
 * - 11: Resume game after error
 * - 20-21: Victory cutscenes
 * - 22: End game
 * 
 * @param game Pointer to the game structure.
 */
void	handle_scenes(t_game *game)
{
	if (game->scene_id == 0)
	{
		show_scene(game, "assets/scenes/intro-louis.xpm");
		my_usleep(3.0);
	}
	else if (game->scene_id == 1)
	{
		game->scene = 0;
		render_map(game);
		return ;
	}
	else if (game->scene_id == 10)
	{
		show_scene(game, "assets/scenes/to-be-continued.xpm");
		my_usleep(3.0);
		ft_printf("\n🎉 WEERK! YOU WIN! 🎉\n");
		ft_printf("Moves: %d\n", game->moves);
		close_game(game);
	}
}

/**
 * @brief Displays a cutscene image filling the entire window.
 * 
 * Loads an XPM image file and displays it in the game window.
 * The image should be the same size as the window (or will be
 * displayed from top-left corner).
 * 
 * @param game Pointer to the game structure.
 * @param file_path Path to the XPM image file to display.
 */
void	show_scene(t_game *game, char *file_path)
{
	t_sprite	scene;

	scene.img = mlx_xpm_file_to_image(game->mlx, file_path,
			&scene.width, &scene.height);
	if (!scene.img)
	{
		ft_printf("Warning: Scene image not found: %s\n", file_path);
		ft_printf("Press ENTER to skip this scene.\n");
		return ;
	}
	scene.addr = mlx_get_data_addr(scene.img, &scene.bpp,
			&scene.line_len, &scene.endian);
	mlx_put_image_to_window(game->mlx, game->win, scene.img, 0, 0);
	mlx_do_sync(game->mlx);
	mlx_destroy_image(game->mlx, scene.img);
}

/**
 * @brief Triggers the victory cutscene sequence.
 * 
 * Called when player successfully collects all items and reaches the exit.
 * Starts the victory cutscene sequence.
 * 
 * @param game Pointer to the game structure.
 */
void	trigger_victory_scene(t_game *game)
{
	game->scene = 1;
	game->scene_id = 10;
	handle_scenes(game);
}

/**
 * @brief Gets the current time in seconds with microsecond precision.
 * 
 * Uses gettimeofday to get high-precision time measurement.
 * 
 * @return Current time as a double (seconds.microseconds).
 */
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

/**
 * @brief Custom sleep function using busy-wait loop.
 * 
 * Since usleep() is forbidden, this implements a precise delay
 * using gettimeofday. The busy-wait ensures accurate timing.
 * 
 * @param seconds Number of seconds to wait (can be fractional).
 */
void	my_usleep(double seconds)
{
	double	start;
	double	end;

	start = get_time();
	end = get_time();
	while (end - start < seconds)
		end = get_time();
}
