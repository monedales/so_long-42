/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/05 17:58:28 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

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

int	main(int argc, char **argv)
{
	char	**map;
	int		error;

	if (argc != 2)
		return (handle_error(ERR_ARGS));
	if (!has_ber_extension(argv[1]))
		return (handle_error(ERR_NOBER));
	map = read_map(argv[1]);
	if (!map)
		return (handle_error(ERR_FILE));
	error = validate_map(map);
	if (error)
	{
		free_map(map);
		return (handle_error(error));
	}
	print_map(map);
	free_map(map);
	return (0);
}
