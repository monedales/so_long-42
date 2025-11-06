/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:56:50 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 16:54:38 by maria-ol         ###   ########.fr       */
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
	ERR_NO_PATH,
	ERR_NO_WIN,
	ERR_MAP_FAILED
}	t_error;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		collected;
	t_point	player_pos;
	t_point	exit_pos;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	wall;
	t_img	background;
	t_img	walkable;
	t_img	collectible;
	t_img	exit;
	t_img	player;
	int		moves;
	int		tile_size;
}	t_game;

typedef struct s_flood_params
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_flood_params;

/**** Map Validation ****/
int		has_ber_extension(const char *filename);
char	**read_map(const char *path);
int		is_rectangular(char **map);
int		has_only_valid_chars(char **map);
int		has_closed_walls(char **map);
int		has_valid_counts(char **map);
int		has_valid_path(char **map);
t_point	find_player(char **map);
char	**create_visited_map(int width, int height);
int		check_accessible(char **map, char **visited, int height);

/**** Game Initialization ****/

/**** Rendering ****/

/**** Utils ****/
char	**ft_append_line(char **map, char *line, int count);
int		handle_error(t_error error);
void	free_map(char **map);
void	free_visited(char **visited);
void	free_visited_partial(char **visited, int until);


#endif