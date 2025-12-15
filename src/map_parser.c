/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/15 12:26:19 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Removes the trailing newline character from a string.
 *
 * This helper function checks if the last character of the string is a
 * newline ('\n') and replaces it with a null terminator to clean up
 * lines read from files.
 * 
 * @param line The string to trim. Must not be NULL.
 *
 * @return The trimmed string (same pointer as input).
 */
static char	*trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

/**
 * @brief Handles errors during map file reading.
 *
 * Cleans up resources by freeing the current line and closing the
 * file descriptor when an error occurs during map parsing.
 * 
 * @param line The current line buffer to free.
 * @param fd The file descriptor to close.
 *
 * @return Always returns NULL to indicate failure.
 */
static char	**handle_read_error(char *line, int fd)
{
	free(line);
	close(fd);
	return (NULL);
}

/**
 * @brief Reads a map file and returns it as a 2D array of strings.
 *
 * Opens the file at the given path, reads it line by line using
 * get_next_line, and builds a dynamically allocated 2D array where
 * each element is a line from the file. Newlines are trimmed from
 * each line. Properly cleans up resources on error or completion.
 * 
 * @param path The path to the map file to read.
 *
 * @return A NULL-terminated array of strings representing the map,
 *         or NULL if the file cannot be opened or memory allocation fails.
 */
char	**read_map(const char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		map = ft_append_line(map, line, count);
		if (!map)
			return (handle_read_error(line, fd));
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

/**
 * @brief Validates that all rows in the map have the same length.
 *
 * Checks if the map forms a proper rectangle by comparing the length
 * of each row to the first row. This ensures the map grid has uniform
 * dimensions required for proper game rendering and collision detection.
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 1 if the map is rectangular (all rows have equal length),
 *         0 if the map is NULL, empty, or has rows of different lengths.
 */
int	is_rectangular(char **map)
{
	int	len;
	int	i;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != (size_t)len)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates that the map contains only allowed characters.
 *
 * Iterates through every character in the map and verifies it matches
 * one of the valid game elements. Valid characters are:
 * - '0': Empty space
 * - '1': Wall
 * - 'C': Collectible
 * - 'E': Exit
 * - 'P': Player starting position
 * - 'M': Enemy mob
 * - 'F': Platform (bonus)
 * - 'G': Ground/floor (bonus)
 * - 'R': Roof/ceiling (bonus)
 * 
 * @param map A NULL-terminated 2D array of strings representing the map.
 *
 * @return 1 if all characters are valid, 0 if any invalid character is found.
 */
int	has_only_valid_chars(char **map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c == '\n')
				break ;
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P'
				&& c != 'F' && c != 'G' && c != 'R' && c != 'M')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
