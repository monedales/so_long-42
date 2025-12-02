/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/02 20:39:35 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Main entry point for the so_long game.
 *
 * Initializes and runs the so_long game. Performs the following steps:
 * 1. Validates command-line arguments (must provide exactly one map file)
 * 2. Checks that the map file has the required .ber extension
 * 3. Reads the map file into memory
 * 4. Validates the map structure, characters, walls, and path to exit
 * 5. Initializes the game window, textures, and renders the initial state
 * 6. Starts the MiniLibX event loop to handle user input
 *
 * The game requires a valid .ber map file with:
 * - Rectangular shape surrounded by walls ('1')
 * - At least one collectible ('C')
 * - Exactly one player starting position ('P')
 * - Exactly one exit ('E')
 * - A valid path from player to all collectibles and the exit
 * 
 * @param argc Argument count. Must be 2 (program name + map file).
 * @param argv Argument vector. argv[1] should be the path to a .ber map file.
 *
 * @return 0 on successful game completion, or an error code if validation
 *         or initialization fails.
 */
int	main(int argc, char **argv)
{
	t_game	game;
	int		error;

	if (argc != 2)
		return (handle_error(ERR_ARGS));
	if (!has_ber_extension(argv[1]))
		return (handle_error(ERR_NOBER));
	game.map.grid = read_map(argv[1]);
	if (!game.map.grid)
		return (handle_error(ERR_FILE));
	error = validate_map(game.map.grid);
	if (error)
	{
		free_map(game.map.grid);
		return (handle_error(error));
	}
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}
