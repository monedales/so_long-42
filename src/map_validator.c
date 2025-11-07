/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:44:06 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_horizontal_walls(char **map, int width, int height)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

static int	check_vertical_walls(char **map, int width, int height)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	has_closed_walls(char **map)
{
	int	width;
	int	height;

	if (!map || !map[0])
		return (0);
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	if (!check_horizontal_walls(map, width, height))
		return (0);
	if (!check_vertical_walls(map, width, height))
		return (0);
	return (1);
}

int	validate_map(char **map)
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
