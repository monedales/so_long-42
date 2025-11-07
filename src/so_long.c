/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 20:59:41 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_map(char **map)
{
	if (!is_rectangular(map))
		return (ERR_NOT_RECTANG);
	if (!has_only_valid_chars(map))
		return (ERR_CHARS_INVALID);
	if (!has_closed_walls(map))
		return (ERR_NOT_WALLS);
	if (!has_valid_counts(map))
		return (ERR_ELEM_INVALID);
	if (!has_valid_path(map))
		return (ERR_NO_PATH);
	return (0);
}

static void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error(ERR_NO_WIN);
	parse_map_dimensions(game);
	parse_map_data(game);
	init_window(game);
	load_textures(game);
	render_map(game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_key_hook(game->win, handle_keypress, game);
}

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
