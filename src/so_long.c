/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/04 20:01:01 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	int		i;

	if (argc != 2)
		return(handle_error(ERR_ARGS));
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
	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
	return (0);
}
