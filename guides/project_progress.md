# 📊 So Long - Project Progress Report

**Date:** November 7, 2025  
**Project:** so_long - Louis vs Ozzy  
**Student:** Mona  
**Campus:** 42 School

---

## 🎯 Project Overview

### Theme
- **Player:** Louis (your cat) 🐱
- **Enemy:** Ozzy (your other cat) 🐱
- **Collectible:** Cheese 🧀
- **Exit:** Cat furniture (where they can jump on)
- **Environment:** Side-view game inspired by your actual house

### Game View
- **Allowed:** Side-view/profile OR top-down (per subject)
- **Chosen:** Side-view with photo-realistic cat sprites

---

## ✅ Completed Features

### FASE 1: Map Validation ✅ (100% Complete)

All validation implemented and tested:

1. **✅ Argument Validation**
   - Checks exactly one argument
   - Error: "Error\nUsage: ./so_long <map.ber>\n"

2. **✅ File Extension Check**
   - Validates `.ber` extension
   - Error: "Error\nMap file must have .ber extension\n"

3. **✅ File Reading**
   - Opens and reads map file
   - Error: "Error\nCannot open map file\n"

4. **✅ Rectangular Map**
   - All lines same length
   - Error: "Error\nMap must be rectangular\n"

5. **✅ Valid Characters**
   - Only allows: `0` (floor), `1` (wall), `C` (collectible), `E` (exit), `P` (player)
   - Error: "Error\nMap contains invalid characters\n"

6. **✅ Closed Walls**
   - Top, bottom, left, right edges all `1`
   - Error: "Error\nMap must be surrounded by walls\n"

7. **✅ Element Counts**
   - Exactly 1 player (`P`)
   - Exactly 1 exit (`E`)
   - At least 1 collectible (`C`)
   - Error: "Error\nMap must have 1 exit, 1 player, and at least 1 collectible\n"

8. **✅ Path Validation (Flood-Fill)**
   - Player can reach all collectibles
   - Player can reach exit after collecting all
   - Error: "Error\nMap must have a valid path to collect all items and reach exit\n"

**Files:**
- `src/map_validator.c` - Main validation functions
- `src/map_parser.c` - File reading
- `src/map_count.c` - Element counting
- `src/pathfinding.c` - Flood-fill algorithm
- `src/error_handler.c` - Centralized error messages

---

### FASE 2: Graphics & Rendering ✅ (95% Complete)

#### Window Management ✅
- **MLX initialization** - Cross-platform (macOS/Linux)
- **Window creation** - Dynamic size based on map
- **Window title** - "So Long and thanx for all the cheese"
- **XQuartz setup** - Working on macOS with DISPLAY=:0

**Files:**
- `src/game_init.c` - Window and MLX initialization
- `Makefile` - Cross-platform build (UNAME_S detection)

#### Texture System ✅
- **XPM loading** - `mlx_xpm_file_to_image()`
- **Image data access** - `mlx_get_data_addr()` for pixel manipulation
- **Texture storage** - `t_sprite` struct with buffer data
- **Error handling** - Graceful failure if texture missing

**Sprites loaded:**
- Wall (`assets/temp/wall.xpm`)
- Floor (`assets/temp/floor.xpm`)
- Collectible (`assets/temp/cheese.xpm`)
- Exit (`assets/temp/exit.xpm`)
- Player (`assets/sprites-louis/louis-front80.xpm`) ⭐ Custom sprite!

**Files:**
- `src/texture_loader.c` - Load and prepare textures

#### Rendering System ✅
- **Frame buffer** - `t_sprite frame` for pixel-perfect rendering
- **Tile-based rendering** - 64x64 tile grid
- **Sprite centering** - Automatic offset calculation
- **Opaque rendering** - `draw_sprite_opaque()` for tiles
- **Transparent rendering** - `draw_sprite_to_frame()` with color keying ⭐

**Transparency System:** 🎨
- **Color key:** `#FF00FF` (Magenta)
- **Method:** Pixel-by-pixel drawing, skip magenta
- **Performance:** Direct buffer access (no `mlx_pixel_put`)
- **Result:** Clean transparent backgrounds! ✨

**Files:**
- `src/render.c` - Main rendering loop
- `src/render_utils.c` - Pixel manipulation functions

---

### Cross-Platform Support ✅

**macOS (Darwin):**
- XQuartz/X11 configuration
- Correct include paths (`/opt/X11`)
- MLX compilation flags
- DISPLAY environment variable

**Linux:**
- Standard X11 paths
- 42 School compatibility
- Tested and working at campus

**Makefile Features:**
- `UNAME_S` detection
- Conditional compilation flags
- Automatic library compilation
- Clean banner output

---

## 🔧 Technical Implementation

### Data Structures

```c
// Point structure
typedef struct s_point {
    int x;
    int y;
} t_point;

// Sprite/Image structure (Enhanced for transparency!)
typedef struct s_sprite {
    void    *img;       // MLX image pointer
    char    *addr;      // Buffer address for pixel access ⭐
    int     width;      // Image width
    int     height;     // Image height
    int     bpp;        // Bits per pixel ⭐
    int     line_len;   // Line length in bytes ⭐
    int     endian;     // Endianness ⭐
} t_sprite;

// Map structure
typedef struct s_map {
    char    **grid;         // 2D map array
    int     width;          // Map width
    int     height;         // Map height
    int     collectibles;   // Total collectibles
    int     collected;      // Collected count
    t_point player_pos;     // Player position
    t_point exit_pos;       // Exit position
} t_map;

// Game structure
typedef struct s_game {
    void     *mlx;          // MLX pointer
    void     *win;          // Window pointer
    t_map    map;           // Map data
    t_sprite wall;          // Wall texture
    t_sprite floor;         // Floor texture
    t_sprite collectible;   // Collectible texture
    t_sprite exit;          // Exit texture
    t_sprite player;        // Player texture
    t_sprite frame;         // Frame buffer ⭐
    int      moves;         // Move counter
    int      tile_size;     // Tile size (64x64)
} t_game;
```

### Key Functions

#### Map Validation
```c
int validate_map(char **map);
int has_ber_extension(const char *filename);
char **read_map(const char *path);
int is_rectangular(char **map);
int has_only_valid_chars(char **map);
int has_closed_walls(char **map);
int has_valid_counts(char **map);
int has_valid_path(char **map);
```

#### Pathfinding (Flood-Fill)
```c
t_point find_player(char **map);
char **create_visited_map(int width, int height);
void flood_fill(char **map, char **visited, int x, int y);
int check_accessible(char **map, char **visited, int height);
```

#### Rendering ⭐
```c
// Initialize frame buffer
void init_window(t_game *game);  // Creates frame buffer

// Opaque rendering (walls, floors, etc.)
void draw_sprite_opaque(t_sprite *frame, t_sprite *sprite, int px, int py);

// Transparent rendering (player with magenta background)
void draw_sprite_to_frame(t_sprite *frame, t_sprite *sprite, int px, int py);

// Main render loop
void render_map(t_game *game);
```

#### Transparency Implementation
```c
#define TRANSPARENT_COLOR 0xFF00FF  // Magenta

static void put_pixel(t_sprite *frame, int x, int y, int color) {
    char *dst;
    if (x < 0 || x >= frame->width || y < 0 || y >= frame->height)
        return;
    dst = frame->addr + (y * frame->line_len + x * (frame->bpp / 8));
    *(unsigned int *)dst = color;
}

static int get_pixel_color(t_sprite *sprite, int x, int y) {
    char *src;
    if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
        return TRANSPARENT_COLOR;
    src = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
    return *(int *)src;
}

void draw_sprite_to_frame(t_sprite *frame, t_sprite *sprite, int px, int py) {
    int x, y, color;
    y = 0;
    while (y < sprite->height) {
        x = 0;
        while (x < sprite->width) {
            color = get_pixel_color(sprite, x, y);
            if (color != TRANSPARENT_COLOR)  // Skip magenta!
                put_pixel(frame, px + x, py + y, color);
            x++;
        }
        y++;
    }
}
```

---

## 📁 Project Structure

```
so_long/
├── Makefile                    # Cross-platform build system
├── so_long                     # Compiled executable
├── include/
│   └── so_long.h              # All structs, prototypes, defines
├── src/
│   ├── so_long.c              # Main entry point
│   ├── error_handler.c        # Centralized error messages
│   ├── map_parser.c           # File reading
│   ├── map_validator.c        # Validation logic
│   ├── map_count.c            # Element counting
│   ├── pathfinding.c          # Flood-fill algorithm
│   ├── game_init.c            # MLX/window/frame buffer init
│   ├── texture_loader.c       # XPM loading with buffer access
│   ├── render.c               # Main rendering loop
│   ├── render_utils.c         # Transparency & pixel functions ⭐
│   ├── events.c               # Event handlers (placeholder)
│   ├── file_utils.c           # File utilities
│   └── free_utils.c           # Memory cleanup
├── libs/
│   ├── libft/                 # Custom library (with ft_append_line)
│   └── minilibix-linux/       # MiniLibX graphics library
├── maps/
│   ├── test.ber               # Small test map
│   ├── medium.ber             # Medium map
│   ├── big.ber                # Large map
│   ├── bad_chars.ber          # Invalid characters test
│   ├── bad_shape.ber          # Non-rectangular test
│   ├── no_path.ber            # Unreachable elements test
│   ├── open_side.ber          # Open walls test
│   └── open_top.ber           # Open walls test
├── assets/
│   ├── sprites-louis/         # Louis cat sprites
│   │   ├── louis-front.jpeg   # Original photo
│   │   └── louis-front80.xpm  # 80x80 sprite with transparency ⭐
│   ├── sprites-ozzy/          # Ozzy cat sprites (bonus)
│   ├── cheese/                # Collectible sprites
│   ├── exit/                  # Exit sprites
│   ├── temp/                  # Placeholder sprites
│   └── so_long-sprites/       # Original sprite references
└── guides/
    ├── README.md                      # Guide index
    ├── flood_fill_explained.md        # Algorithm explanation
    ├── map_validation_guide.md        # Validation rules
    ├── game_structure.md              # Struct organization
    ├── fase2_visual_prep.md           # Visual assets prep
    ├── asset_conversion.md            # JPEG to XPM workflow
    ├── sprite_creation_guide.md       # ImageMagick commands ⭐
    └── project_progress.md            # This file! ⭐
```

---

## 🎨 Asset Creation Progress

### Completed ✅
- **Louis front sprite** - 80x80, transparent background
- **Magenta color keying** - Working perfectly!
- **Manual XPM editing** - Background color changed to #FF00FF

### In Progress 🔄
- Cheese collectible sprite
- Cat furniture exit sprite
- Ozzy enemy sprite (bonus)

### Workflow Established ✅
1. Crop photo in Preview
2. Export as JPEG
3. Convert with ImageMagick
4. Edit XPM to set background to #FF00FF
5. Test in game

**Command:**
```bash
magick input.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm
```

---

## 🚧 Pending Features

### FASE 3: Player Movement (Next!)
- [ ] Keyboard event handling
  - [ ] W/A/S/D or Arrow keys
  - [ ] ESC to exit
- [ ] Player position update
- [ ] Collision detection
- [ ] Move counter increment
- [ ] Render on movement

### FASE 4: Game Logic
- [ ] Collectible pickup
  - [ ] Remove C from map when collected
  - [ ] Increment collected counter
- [ ] Exit validation
  - [ ] Only allow exit when all collected
- [ ] Win condition
  - [ ] Display win message
  - [ ] Close game

### FASE 5: Polish
- [ ] Move counter display on screen
- [ ] Win/lose messages
- [ ] ESC key to exit
- [ ] Window close button (X)

### Bonus Features
- [ ] Ozzy enemy with AI
  - [ ] Random/chase movement
  - [ ] Collision = lose
- [ ] Animations
  - [ ] Walking sprites (4 directions)
  - [ ] Collectible animation
  - [ ] Frame-based animation system
- [ ] On-screen move counter
  - [ ] Rendered as text/sprite

---

## 🏆 Achievements

### Technical Milestones
- ✅ Cross-platform Makefile (macOS + Linux)
- ✅ Complete flood-fill pathfinding
- ✅ Pixel-perfect transparency system
- ✅ Frame buffer rendering
- ✅ Direct buffer manipulation (no mlx_pixel_put)
- ✅ Custom cat sprite from photo

### Learning Highlights
- **Flood-fill algorithm** - Recursive pathfinding
- **Color keying** - Green screen technique for games
- **ImageMagick** - Command-line image processing
- **XPM format** - Understanding indexed color images
- **MLX buffer access** - `mlx_get_data_addr()` for pixel manipulation
- **Modular architecture** - 12 source files, clean separation

### Problem-Solving Wins
- Fixed XPM transparency issues (c None unreliable)
- Implemented manual color keying (#FF00FF method)
- Created frame buffer for mixed rendering
- Separated opaque vs transparent rendering
- Auto-centering sprites with offset calculation

---

## 📊 Statistics

### Code Metrics
- **Source files:** 12 (C files)
- **Header files:** 1 (so_long.h)
- **Library files:** 2 (libft, minilibx)
- **Map test files:** 8
- **Guide documents:** 7
- **Total documentation:** ~3500 lines

### Compilation
- **Compiler:** gcc/cc
- **Flags:** `-Wall -Wextra -Werror`
- **Platform:** macOS (Darwin) & Linux
- **Libraries:** libft, MLX, X11, Xext, m, z

### Testing
- ✅ Valid maps load correctly
- ✅ Invalid maps rejected with proper errors
- ✅ Window opens and renders
- ✅ Sprites load with transparency
- ✅ Louis appears cleanly on map
- ✅ Works at 42 School (Linux)
- ✅ Works on Mac (XQuartz)

---

## 🎯 Next Steps

### Immediate (Today/Tomorrow)
1. **Create remaining sprites**
   - Cheese collectible
   - Cat furniture exit
   - Wall/floor tiles (if replacing temp)

2. **Implement player movement**
   - Set up key hooks
   - Update player position
   - Check collisions with walls
   - Increment move counter

### Short Term (This Week)
3. **Add game logic**
   - Collectible pickup
   - Exit unlock when all collected
   - Win condition

4. **Polish rendering**
   - Smooth movement
   - Move counter display
   - Win message

### Optional (Bonus)
5. **Ozzy enemy AI**
   - Patrol/chase behavior
   - Collision detection
   - Lose condition

6. **Animations**
   - Walking frames
   - Idle animations
   - Collectible glow

---

## 📝 Notes & Observations

### What Worked Well
- Modular code structure from the start
- Comprehensive validation before rendering
- Testing with multiple maps
- Using real photos for sprites (unique theme!)
- Color keying method (reliable transparency)

### Challenges Overcome
- XPM transparency (`c None` doesn't work with MLX)
- Frame buffer implementation (mixed rendering)
- Cross-platform compilation (UNAME_S detection)
- ImageMagick learning curve
- Sprite sizing (found 80x80 sweet spot)

### Tips for Future
- Always test invalid cases early
- Document commands in guides (save time!)
- Create test maps as you code
- Keep sprites organized by type
- Use #FF00FF for transparency (industry standard)

---

## 🔗 Resources Used

### Documentation
- 42 Subject - so_long project requirements
- MiniLibX Docs - https://harm-smits.github.io/42docs/libs/minilibx
- ImageMagick - https://imagemagick.org/
- XPM Format - https://en.wikipedia.org/wiki/X_PixMap

### Tools
- VS Code - Primary IDE
- ImageMagick - Sprite conversion
- Preview (macOS) - Image cropping
- XQuartz - X11 for macOS
- Git - Version control

### Guides Created
All guides in `guides/` folder - comprehensive documentation for every aspect of the project!

---

**Project Status:** 🟢 On Track  
**Current Phase:** FASE 2 Complete → Moving to FASE 3  
**Mood:** 🎉 Transparency working! Ready for movement!  
**Next Session:** Implement keyboard controls and player movement

---

**Last Updated:** November 7, 2025  
**Time Invested:** ~15 hours (coding + debugging + sprite creation)  
**Coffee Consumed:** ☕☕☕☕ (at least!)
