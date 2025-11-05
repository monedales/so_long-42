/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/05 14:51:57 by maria-ol         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
		return (handle_error(ERR_ARGS));
	if (!has_ber_extension(argv[1]))
		return (handle_error(ERR_NOBER));
	map = read_map(argv[1]);
	if (!map)
		return (handle_error(ERR_FILE));
	if (!is_rectangular(map))
		return (handle_error(ERR_NOT_RECTANG));
	if (!has_only_valid_chars(map))
		return (handle_error(ERR_CHARS_INVALID));
	if (!has_closed_walls(map))
		return (handle_error(ERR_NOT_WALLS));
	if (!has_valid_counts(map))
		return (handle_error(ERR_ELEM_INVALID));
	if (!has_valid_path(map))
		return (handle_error(ERR_NO_PATH));
	print_map(map);
	return (0);
}
