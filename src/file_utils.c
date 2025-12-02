/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:30:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/12/02 20:29:17 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the filename has the required .ber extension.
 *
 * Validates that the provided filename ends with the ".ber" extension,
 * which is required for map files in the so_long game. The function
 * performs a string comparison on the last 4 characters of the filename.
 * 
 * @param filename The filename string to validate. Must not be NULL.
 *
 * @return 1 if the filename has the .ber extension, 0 otherwise.
 * @retval 0 If filename is NULL or shorter than 4 characters.
 * @retval 1 If filename ends with ".ber".
 */
int	has_ber_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}
