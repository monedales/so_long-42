/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:43:18 by mona              #+#    #+#             */
/*   Updated: 2025/11/04 19:14:37 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_error(t_error error)
{
    static const char   *messages[] = {
        NULL,
        "Error\ninvalid arguments\n",
		"Error\ninvalid file\n",
		"Error\nmissing .ber extension\n",
		"Error\nmap is not rectangular\n",
		"Error\nmap has invalid characters\n",
		"Error\nmap is not closed by walls\n",
        "Error\ninvalid number of elements (P/E/C)\n"
    };
    if (error > 0 && error < (int)(sizeof(messages) / sizeof(messages[0])))
    {
        ft_printf("%s", messages[error]);
    }
    return (1);
}