/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:56:50 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/04 19:58:18 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define KEW_W 119
# define KEW_S 115
# define KEW_A 97
# define KEW_D 100
# define KEW_ESC 65307

# include <stdio.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibix-linux/mlx.h"
# include "../libs/minilibix-linux/mlx_int.h"

typedef enum e_error
{
    ERR_ARGS = 1,
	ERR_FILE,
	ERR_NOBER,
	ERR_NOT_RECTANG,
	ERR_CHARS_INVALID,
	ERR_NOT_WALLS,
    ERR_ELEM_INVALID,
	ERR_NO_PATH
}   t_error;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int	handle_error(t_error error);
int	has_ber_extension(const char *filename);
char **read_map(const char *path);
int	is_rectangular(char **map);
int	has_only_valid_chars(char **map);
int	has_closed_walls(char **map);
char	**ft_append_line(char **map, char *line, int count);
int	has_valid_counts(char **map);
int	has_valid_path(char **map);

#endif