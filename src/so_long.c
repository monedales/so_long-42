/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/04 19:18:46 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	int		i;

	if (argc != 2)
		return(handle_error(ERR_ARGS));
	// if (!has_ber_extension(argv[1]))
	// 	return (handle_error(ERR_NO_BER));
	map = read_map(argv[1]);
	if (!map)
		handle_error(ERR_FILE);
	if (!is_rectangular(map))
		handle_error(ERR_NOT_RECTANG);
	if (!has_only_valid_chars(map))
		handle_error(ERR_CHARS_INVALID);
	if (!has_closed_walls(map))
		handle_error(ERR_NOT_WALLS);
	if (!has_valid_counts(map))
		handle_error(ERR_ELEM_INVALID);
	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
	return (0);
}
