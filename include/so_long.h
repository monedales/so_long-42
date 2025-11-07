/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:56:50 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:28 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307

# include "../libs/libft/libft.h"
# include "../libs/minilibix-linux/mlx.h"
# include "../libs/minilibix-linux/mlx_int.h"
# include <stdio.h>

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
}				t_error;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_sprite
{
	void		*img;
	int			width;
	int			height;
}				t_sprite;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			collected;
	t_point		player_pos;
	t_point		exit_pos;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_sprite	wall;
	t_sprite	floor;
	t_sprite	collectible;
	t_sprite	exit;
	t_sprite	player;
	int			moves;
	int			tile_size;
}				t_game;

typedef struct s_flood_params
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_flood_params;

/**** Map Validation ****/
int				validate_map(char **map);
int				has_ber_extension(const char *filename);
char			**read_map(const char *path);
int				is_rectangular(char **map);
int				has_only_valid_chars(char **map);
int				has_closed_walls(char **map);
int				has_valid_counts(char **map);
int				has_valid_path(char **map);
t_point			find_player(char **map);
char			**create_visited_map(int width, int height);
int				check_accessible(char **map, char **visited, int height);

/**** Game Initialization ****/
void			init_game(t_game *game);
void			parse_map_data(t_game *game);
void			parse_map_dimensions(t_game *game);
void			init_window(t_game *game);
void			load_textures(t_game *game);
void			render_map(t_game *game);

/**** Utils ****/
// char			**ft_append_line(char **map, char *line, int count);
int				handle_error(t_error error);
void			free_map(char **map);
void			free_visited(char **visited);
void			free_visited_partial(char **visited, int until);

/**** Event Handlers ****/
int				handle_keypress(int keycode, t_game *game);
int				handle_close(t_game *game);
int				close_game(t_game *game);

#endif