/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:00:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/10 20:00:16 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Handles the window close event.
 *
 * Called when the user clicks the window's close button (X).
 * Triggers complete game cleanup and program termination by calling
 * close_game(), which frees all resources and exits gracefully.
 *
 * This function is registered as a hook for the window destroy event
 * (event 17) in MiniLibX.
 * 
 * @param game Pointer to the game structure containing all resources.
 *
 * @return Always returns 0 (required by MiniLibX hook system, but the
 *         function calls exit() so this value is never actually used).
 */
int	handle_close(t_game *game)
{
	close_game(game);
	return (0);
}

/**
 * @brief Updates cheese animation cycling through collectible types.
 * 
 * @param game Pointer to the game structure.
 */
static void	update_cheese_anim(t_game *game)
{
	int	old_cheese;

	game->cheese_counter++;
	if (game->cheese_counter >= CHEESE_DELAY)
	{
		game->cheese_counter = 0;
		old_cheese = game->cheese_frame;
		game->cheese_frame = (game->cheese_frame + 1) % 5;
		if (old_cheese != game->cheese_frame)
			render_map(game);
	}
}

/**
 * @brief Updates player idle animation with tail-wagging effect.
 * 
 * @param game Pointer to the game structure.
 * @param counter Static counter for animation timing.
 */
static void	update_player_anim(t_game *game, int *counter)
{
	int	old_frame;

	if (game->player.anim_counter < IDLE_WAIT)
		return ;
	(*counter)++;
	if (*counter >= ANIM_DELAY)
	{
		*counter = 0;
		old_frame = game->player.frame;
		game->player.frame = (game->player.frame + 1) % IDLE_FRAMES;
		if (old_frame != game->player.frame)
			render_map(game);
	}
}

/**
 * @brief Main animation loop hook called by MiniLibX.
 * 
 * @param param Pointer to the game structure.
 * @return Always returns 0.
 */
int	update_animation(void *param)
{
	t_game			*game;
	static int		counter = 0;

	game = (t_game *)param;
	game->player.anim_counter++;
	update_cheese_anim(game);
	update_player_anim(game, &counter);
	return (0);
}
