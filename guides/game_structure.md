# 🏗️ Game Structure - Architecture Guide

## 📖 Overview

This guide explains how to organize your game data and structs for FASE 2 onwards.

---

## 🎯 Why Do We Need Structs?

**FASE 1:** Simple validation - just `char **map` was enough  
**FASE 2+:** Need to track:
- Window handle
- Image pointers
- Player position
- Collectibles count
- Movement counter
- Map data
- And more!

**Solution:** Organize everything in structs!

---

## 🏗️ Core Structs

### 1. **Position Struct** (Already have this!)

```c
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;
```

**Usage:**
```c
t_point	player_pos;
player_pos.x = 5;
player_pos.y = 3;
```

---

### 2. **Image Struct**

```c
typedef struct s_img
{
	void	*img;      // Image pointer from mlx
	int		width;     // Image width in pixels
	int		height;    // Image height in pixels
}	t_img;
```

**Why?** Keep image data organized together.

**Usage:**
```c
t_img	wall;
wall.img = mlx_xpm_file_to_image(mlx, "wall.xpm", &wall.width, &wall.height);
```

---

### 3. **Map Struct**

```c
typedef struct s_map
{
	char	**grid;         // The actual map (2D array)
	int		width;          // Map width in tiles
	int		height;         // Map height in tiles
	int		collectibles;   // Total collectibles
	int		collected;      // Collectibles collected so far
	t_point	player_pos;     // Player starting position
	t_point	exit_pos;       // Exit position
}	t_map;
```

**Why?** Centralize all map-related data.

---

### 4. **Main Game Struct**

```c
typedef struct s_game
{
	void	*mlx;           // MLX instance
	void	*win;           // Window pointer
	t_map	map;            // Map data
	t_img	wall;           // Wall sprite
	t_img	floor;          // Floor sprite
	t_img	collectible;    // Collectible sprite
	t_img	exit;           // Exit sprite
	t_img	player;         // Player sprite
	int		moves;          // Movement counter
	int		tile_size;      // Size of each tile (64, 32, etc.)
}	t_game;
```

**Why?** Central hub - everything accessible from one struct!

---

## 🎯 How They Work Together

### Example: Rendering the Map

```c
void	render_map(t_game *game)
{
	int	x, y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			// Render floor first (background)
			render_tile(game, &game->floor, x, y);
			
			// Render what's on this tile
			if (game->map.grid[y][x] == '1')
				render_tile(game, &game->wall, x, y);
			else if (game->map.grid[y][x] == 'C')
				render_tile(game, &game->collectible, x, y);
			else if (game->map.grid[y][x] == 'E')
				render_tile(game, &game->exit, x, y);
			else if (game->map.grid[y][x] == 'P')
				render_tile(game, &game->player, x, y);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, t_img *img, int map_x, int map_y)
{
	int	screen_x;
	int	screen_y;

	screen_x = map_x * game->tile_size;
	screen_y = map_y * game->tile_size;
	mlx_put_image_to_window(game->mlx, game->win, img->img, screen_x, screen_y);
}
```

---

## 🔄 Initialization Flow

### Step 1: Create and Zero the Game Struct

```c
int	main(int argc, char **argv)
{
	t_game	game;

	// Zero out the struct (good practice)
	ft_memset(&game, 0, sizeof(t_game));
	
	// Initialize MLX
	game.mlx = mlx_init();
	if (!game.mlx)
		return (handle_error(ERR_MLX));
	
	// Continue setup...
}
```

---

### Step 2: Load and Validate Map

```c
void	init_map(t_game *game, char *filepath)
{
	// Load map (your FASE 1 function!)
	game->map.grid = read_map(filepath);
	if (!game->map.grid)
		exit_error(game, "Failed to load map");
	
	// Validate (your FASE 1 functions!)
	if (!is_rectangular(game->map.grid))
		exit_error(game, "Map not rectangular");
	// ... all other validations
	
	// Calculate dimensions
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(game->map.grid[0]);
	
	// Find positions and count collectibles
	parse_map_data(game);
}
```

---

### Step 3: Parse Map Data

```c
void	parse_map_data(t_game *game)
{
	int	x, y;

	game->map.collectibles = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'P')
			{
				game->map.player_pos.x = x;
				game->map.player_pos.y = y;
			}
			else if (game->map.grid[y][x] == 'E')
			{
				game->map.exit_pos.x = x;
				game->map.exit_pos.y = y;
			}
			else if (game->map.grid[y][x] == 'C')
				game->map.collectibles++;
			x++;
		}
		y++;
	}
	game->map.collected = 0;
	game->moves = 0;
}
```

---

### Step 4: Create Window

```c
void	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	game->tile_size = 64;  // Or 32, your choice
	
	win_width = game->map.width * game->tile_size;
	win_height = game->map.height * game->tile_size;
	
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long - Louis vs Ozzy");
	if (!game->win)
		exit_error(game, "Failed to create window");
}
```

---

### Step 5: Load Sprites

```c
void	load_sprites(t_game *game)
{
	game->wall.img = mlx_xpm_file_to_image(game->mlx, 
		"assets/sprites/wall.xpm", &game->wall.width, &game->wall.height);
	if (!game->wall.img)
		exit_error(game, "Failed to load wall sprite");
	
	game->floor.img = mlx_xpm_file_to_image(game->mlx,
		"assets/sprites/floor.xpm", &game->floor.width, &game->floor.height);
	if (!game->floor.img)
		exit_error(game, "Failed to load floor sprite");
	
	// ... load all other sprites
}
```

---

## 🧹 Cleanup Function

**IMPORTANT:** Always free resources on exit!

```c
void	cleanup_game(t_game *game)
{
	// Free images
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	
	// Free window
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	
	// Free map
	if (game->map.grid)
		ft_free_arr(game->map.grid);
	
	// MLX cleanup (if needed on your system)
	// Some systems need mlx_destroy_display(game->mlx);
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
```

---

## 🎮 Complete Main Structure

```c
int	main(int argc, char **argv)
{
	t_game	game;

	// Validate arguments
	if (argc != 2)
		return (handle_error(ERR_ARGS));
	if (!has_ber_extension(argv[1]))
		return (handle_error(ERR_NOBER));
	
	// Initialize game struct
	ft_memset(&game, 0, sizeof(t_game));
	
	// Initialize MLX
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	
	// Load and validate map
	init_map(&game, argv[1]);
	
	// Create window
	init_window(&game);
	
	// Load sprites
	load_sprites(&game);
	
	// Render initial state
	render_map(&game);
	
	// Set up hooks
	mlx_hook(game.win, 17, 0, close_game, &game);        // Close button
	mlx_key_hook(game.win, handle_keypress, &game);      // Keyboard
	
	// Start game loop
	mlx_loop(game.mlx);
	
	return (0);
}
```

---

## 🎯 Benefits of This Structure

### 1. **Everything in One Place**
```c
// Bad:
void render(void *mlx, void *win, char **map, void *wall_img, ...)

// Good:
void render(t_game *game)  // Everything accessible!
```

### 2. **Easy to Pass Around**
```c
// Only need to pass one pointer
mlx_hook(win, 2, 0, handle_keypress, &game);
```

### 3. **Easy to Extend**
```c
// Want to add sound? Just add to struct:
typedef struct s_game
{
	// ... existing fields
	void	*sound_engine;
	int		volume;
}	t_game;
```

### 4. **Clear Organization**
```c
game.map.collectibles     // Map-related
game.wall.img             // Sprite-related
game.moves                // Game state
```

---

## 📋 Header File Organization

### so_long.h structure:

```c
#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"

// Defines
# define TILE_SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

// Error enum (you already have this)
typedef enum e_error
{
	// ... your errors
}	t_error;

// Structs
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
	t_img	floor;
	t_img	collectible;
	t_img	exit;
	t_img	player;
	int		moves;
	int		tile_size;
}	t_game;

// Function prototypes
// Map validation (FASE 1)
int		has_ber_extension(const char *filename);
char	**read_map(const char *path);
int		is_rectangular(char **map);
int		has_only_valid_chars(char **map);
int		has_closed_walls(char **map);
int		has_valid_counts(char **map);
int		has_valid_path(char **map);

// Game initialization (FASE 2)
void	init_map(t_game *game, char *filepath);
void	init_window(t_game *game);
void	load_sprites(t_game *game);
void	parse_map_data(t_game *game);

// Rendering (FASE 2)
void	render_map(t_game *game);
void	render_tile(t_game *game, t_img *img, int x, int y);

// Game logic (FASE 3)
int		handle_keypress(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);

// Utils
int		close_game(t_game *game);
void	cleanup_game(t_game *game);
int		handle_error(t_error error);

#endif
```

---

## 🚀 Next Steps

1. ✅ Understand the struct organization
2. ✅ Add new structs to `so_long.h`
3. → Create `init_game.c` with initialization functions
4. → Create `render.c` with rendering functions
5. → Update Makefile to compile new files

---

## 💡 Pro Tips

1. **Use `ft_memset`** to zero structs: `ft_memset(&game, 0, sizeof(t_game))`
2. **Check every allocation**: Always verify `mlx_init()`, `mlx_new_window()`, etc. return non-NULL
3. **Initialize in order**: MLX → Map → Window → Sprites
4. **Always cleanup**: Use `cleanup_game()` before every exit
5. **Consistent naming**: `game->map.player_pos` not `game->plyr_x`

---

## ✅ Understanding Check

Can you answer:
1. Why do we need a `t_game` struct?
2. What's the difference between `t_point` and `t_map`?
3. Why store both `collectibles` and `collected`?
4. When should you call `cleanup_game()`?
5. Why pass `&game` to MLX hooks instead of copying?

<details>
<summary>Answers</summary>

1. To organize all game data in one place, easy to pass around
2. `t_point` is a position (x,y), `t_map` contains map data
3. `collectibles` = total in map, `collected` = how many picked up so far
4. Before every `exit()` - on errors and normal game end
5. MLX needs a pointer to the actual struct, not a copy

</details>

---

**Your game structure is the skeleton of your project - build it solid!** 🏗️💪
