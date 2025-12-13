/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:43:18 by mona              #+#    #+#             */
/*   Updated: 2025/12/13 16:52:17 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Centralized error handler for the so_long game.
 *
 * This function manages all error messages through a static lookup table that
 * maps error codes from the t_error enum to their corresponding error messages.
 * All messages follow the format "Error\n<description>\n" for consistency.
 *
 * The function uses array indexing for O(1) lookup time and avoids repetitive
 * if-else chains. Messages are stored as const char* for memory efficiency.
 *
 * @param error Error code from the t_error enum. Valid values:
 *              - ERR_ARGS: Invalid number of command-line arguments
 *              - ERR_FILE: File cannot be opened or read
 *              - ERR_NOBER: File lacks .ber extension
 *              - ERR_NOT_RECTANG: Map is not rectangular
 *              - ERR_CHARS_INVALID: Map contains invalid characters
 *              - ERR_NOT_WALLS: Map perimeter is not fully walled
 *              - ERR_ELEM_INVALID: Invalid count of P/E/C elements
 *              - ERR_NO_PATH: No valid path to all collectibles and exit
 * 				- ERR_NO_WIN: failed to create window
 *				- ERR_MAP_FAILED: failed to load map
 *				- ERR_TEXTURE_FAILED: failed to load texture
 *
 * @return Always returns 1 to indicate error status for main() exit code.
 *
 * @note The first element (index 0) is NULL as error codes start at 1.
 *
 * @see t_error enum definition in so_long.h
 * @see main() in so_long.c for usage examples
 */
int	handle_error(t_error error)
{
	static const char	*messages[] = {
		NULL,
		"Error\ninvalid arguments\n",
		"Error\ninvalid file\n",
		"Error\nmissing .ber extension\n",
		"Error\nmap is not rectangular\n",
		"Error\nmap has invalid characters\n",
		"Error\nmap is not closed by walls\n",
		"Error\ninvalid number of elements (P/E/C)\n",
		"Error\nno valid path (unreachable collectibles or exit)\n",
		"Error\nfailed to create window\n",
		"Error\nfailed to load map\n",
		"Error\nfailed to load texture: "
	};

	if (error > 0 && error < (int)(sizeof(messages) / sizeof(messages[0])))
	{
		ft_printf("%s", messages[error]);
	}
	return (1);
}
