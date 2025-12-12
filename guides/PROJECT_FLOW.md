# 🎮 So Long - Project Flow Complete

## 📋 Table of Contents
1. [Program Start](#program-start)
2. [Map Loading & Validation](#map-loading--validation)
3. [Game Initialization](#game-initialization)
4. [Cutscene System](#cutscene-system)
5. [Game Loop](#game-loop)
6. [Event Handling](#event-handling)
7. [Rendering Pipeline](#rendering-pipeline)
8. [Game End](#game-end)

---

## 🚀 Program Start

### Main Function Flow
```
main(argc, argv)
    ├─ Validate arguments (argc == 2)
    ├─ Check .ber extension
    ├─ Read map file → grid[][]
    ├─ Validate map structure
    ├─ init_game()
    └─ mlx_loop() → Game Loop
```

**File:** `src/so_long.c`

**Steps:**
1. **Argument Validation**
   - Must have exactly 2 arguments (program + map file)
   - Returns `ERR_ARGS` if incorrect

2. **File Extension Check**
   - Map must end with `.ber`
   - Returns `ERR_NOBER` if invalid

3. **Map Loading**
   - Calls `read_map(argv[1])`
   - Reads entire file into `char **grid`
   - Returns `ERR_FILE` if file can't be opened

4. **Map Validation**
   - Calls `validate_map(grid)`
   - Checks structure, walls, characters, path
   - Returns specific error code if invalid

5. **Game Initialization**
   - Calls `init_game(&game)`
   - Sets up everything needed to run

6. **Start Loop**
   - `mlx_loop(game.mlx)` - infinite loop until exit

---

## 🗺️ Map Loading & Validation

### Map Reading Process
```
read_map(filename)
    ├─ Open file
    ├─ get_next_line() for each line
    ├─ Store in char **grid
    └─ Return grid
```

**File:** `src/file_utils.c`

### Map Validation Flow
```
validate_map(grid)
    ├─ Check rectangular shape
    ├─ Check walls on all borders
    ├─ Count map elements
    │   ├─ Must have ≥1 'C' (collectible)
    │   ├─ Must have ==1 'P' (player)
    │   └─ Must have ==1 'E' (exit)
    ├─ Check invalid characters
    └─ Validate path (flood fill)
        ├─ Can reach all collectibles?
        └─ Can reach exit?
```

**Files:**
- `src/map_validator.c` - Main validation
- `src/map_count.c` - Element counting
- `src/pathfinding.c` - Flood fill algorithm

**Validation Errors:**
- `ERR_SHAPE` - Not rectangular
- `ERR_WALLS` - Missing border walls
- `ERR_P` - No player or multiple players
- `ERR_E` - No exit or multiple exits
- `ERR_C` - No collectibles
- `ERR_CHARS` - Invalid characters
- `ERR_PATH` - No valid path to collectibles/exit

---

## 🎯 Game Initialization

### init_game() Flow
```
init_game(game)
    ├─ mlx_init() → Initialize MiniLibX
    ├─ parse_map_dimensions() → Get width/height
    ├─ parse_map_data() → Find player, exit, collectibles
    ├─ init_window() → Create window + frame buffer
    ├─ init_camera() → Setup viewport system
    ├─ load_textures() → Load all sprites
    ├─ Setup cutscene (scene = 1, scene_id = 0)
    ├─ handle_scenes() → Show intro
    ├─ mlx_hook() → Setup close button handler
    ├─ mlx_key_hook() → Setup keyboard handler
    └─ mlx_loop_hook() → Setup animation loop
```

**File:** `src/game_init.c`

### Window Creation
```
init_window(game)
    ├─ Calculate window size
    │   ├─ map_width * 64 (max 800px)
    │   └─ map_height * 64 (max 600px)
    ├─ mlx_new_window()
    ├─ Create frame buffer image
    └─ Store window dimensions
```

### Camera System
```
init_camera(game)
    ├─ Center on player position
    ├─ Calculate viewport boundaries
    └─ Adjust if map smaller than window
```

### Texture Loading
```
load_textures(game)
    ├─ Load tile sprites (wall, floor, exit, etc.)
    ├─ Load player sprites (idle, walk, directions)
    ├─ Load collectible sprites (cheese frames)
    ├─ Convert XPM files to MLX images
    └─ Store all in game.textures struct
```

---

## 🎬 Cutscene System

### Scene Flow
```
Intro Scene (scene_id = 0)
    ├─ show_scene("intro-louis.xpm")
    ├─ my_usleep(3.0) → Wait 3 seconds
    └─ Wait for ENTER press

Start Game (scene_id = 1)
    ├─ Disable scene mode (scene = 0)
    ├─ render_map() → Draw game
    └─ Enable player control

Victory Scene (scene_id = 10)
    ├─ show_scene("to-be-continued.xpm")
    ├─ my_usleep(2.0) → Wait 2 seconds
    ├─ Print victory message
    └─ close_game() → Auto-exit
```

**File:** `src/scenes.c`

### Scene Display Process
```
show_scene(game, filepath)
    ├─ mlx_xpm_file_to_image() → Load image
    ├─ mlx_put_image_to_window() → Display
    ├─ mlx_do_sync() → Force screen update
    └─ mlx_destroy_image() → Free image
```

### Custom Sleep (42-compliant)
```
my_usleep(seconds)
    ├─ get_time() → Start time
    └─ Busy-wait loop until elapsed
        └─ get_time() - start >= seconds
```

Uses `gettimeofday()` for microsecond precision (no `usleep()` allowed by 42).

---

## 🔄 Game Loop

### Main Loop (mlx_loop)
```
mlx_loop(mlx)
    └─ Infinite loop:
        ├─ Process X11 events
        ├─ Call loop_hook → update_animation()
        ├─ Handle keyboard events → handle_keypress()
        └─ Handle window close → handle_close()
```

### Animation Update (every frame)
```
update_animation(game)
    ├─ Update frame counter
    ├─ Check animation delays
    ├─ Update player sprite
    │   ├─ Switch walk frames
    │   ├─ Handle idle animation
    │   └─ Update direction
    ├─ Update collectible sprites (cheese animation)
    └─ render_map() → Redraw everything
```

**File:** `src/events_animation.c`

**Animation Timing:**
- Walk animation: Every 5000 frames
- Idle animation: After 300000 frames stationary
- Collectible: Every 20000 frames

---

## ⌨️ Event Handling

### Keyboard Input Flow
```
handle_keypress(keycode, game)
    ├─ If in scene mode AND keycode == ENTER:
    │   ├─ scene_id++
    │   └─ handle_scenes() → Next scene
    │
    ├─ If keycode == ESC:
    │   └─ close_game() → Exit
    │
    └─ If movement key (WASD/Arrows):
        └─ handle_movement() → Try to move player
```

**File:** `src/events.c`

### Movement Processing
```
handle_movement(keycode, game)
    ├─ Determine direction (UP/DOWN/LEFT/RIGHT)
    ├─ Calculate new position (new_x, new_y)
    └─ move_player(game, new_x, new_y)
```

### Player Movement Logic
```
move_player(game, new_x, new_y)
    ├─ is_valid_move()?
    │   ├─ Check boundaries
    │   ├─ Check walls/platforms
    │   └─ Return 0 if blocked
    │
    ├─ Check tile at new position:
    │   ├─ 'C' → Collect item
    │   │   ├─ collectibles_collected++
    │   │   └─ Remove from map
    │   │
    │   ├─ 'E' → Check if can exit
    │   │   ├─ If all collected:
    │   │   │   ├─ render_map()
    │   │   │   └─ trigger_victory_scene()
    │   │   └─ Else: Can walk over exit
    │   │
    │   └─ '0'/'P' → Normal move
    │
    ├─ Update player position
    ├─ Update map grid
    ├─ Increment move counter
    ├─ Update camera
    ├─ Reset idle timer
    └─ render_map()
```

### Victory Trigger
```
trigger_victory_scene(game)
    ├─ Set scene = 1 (enable scene mode)
    ├─ Set scene_id = 10 (victory scene)
    └─ handle_scenes() → Show victory + close
```

---

## 🎨 Rendering Pipeline

### Complete Render Flow
```
render_map(game)
    ├─ Clear frame buffer
    ├─ Calculate visible area (camera viewport)
    ├─ For each visible tile:
    │   ├─ Draw base tile (floor/wall)
    │   ├─ Draw decorations (platform, roof, etc.)
    │   ├─ Draw collectibles (if present)
    │   └─ Draw exit (if present)
    │
    ├─ Draw player sprite
    │   ├─ Select sprite based on:
    │   │   ├─ Direction (front/back/left/right)
    │   │   ├─ State (idle/walk)
    │   │   └─ Frame number
    │   └─ Draw with transparency
    │
    ├─ Draw move counter HUD
    └─ mlx_put_image_to_window() → Display frame
```

**Files:**
- `src/render.c` - Main rendering
- `src/render_tiles.c` - Tile drawing
- `src/render_utils.c` - Sprite utilities
- `src/camera.c` - Viewport calculations

### Camera Viewport System
```
Camera bounds (800x600 max window)
    ├─ If map <= viewport: Show entire map
    │
    └─ If map > viewport: Follow player
        ├─ Center camera on player
        ├─ Clamp to map boundaries
        └─ Calculate visible tiles
```

### Sprite Rendering
```
put_sprite(game, sprite, x, y)
    ├─ Calculate screen position
    ├─ For each pixel:
    │   ├─ Get color from sprite
    │   ├─ If color != TRANSPARENT (0xFF00FF):
    │   │   └─ Draw pixel to frame buffer
    │   └─ Skip transparent pixels
    └─ Continue
```

### Move Counter Display
```
print_moves(game)
    ├─ Format: "Moves: XXX"
    ├─ Position: Top-left corner
    ├─ Color: White text
    └─ Updates every frame
```

---

## 🏁 Game End

### Normal Exit Flow
```
ESC Key Pressed
    └─ handle_keypress()
        └─ close_game(game)
            ├─ free_textures() → Free all sprites
            ├─ mlx_destroy_window() → Close window
            ├─ free_map() → Free map grid
            ├─ mlx_destroy_display() → Close X11
            ├─ free(mlx) → Free MLX struct
            └─ exit(0) → Clean exit
```

### Victory Exit Flow
```
Collect All + Go to Exit
    └─ trigger_victory_scene()
        └─ handle_scenes(scene_id = 10)
            ├─ show_scene("to-be-continued.xpm")
            ├─ my_usleep(2.0)
            ├─ ft_printf("🎉 WEERK! YOU WIN! 🎉")
            ├─ ft_printf("Moves: %d")
            └─ close_game() → Clean exit
```

### Window Close Button
```
Click [X] on window
    └─ mlx_hook(17, ..., handle_close, game)
        └─ close_game(game)
            └─ [Same cleanup as ESC]
```

**File:** `src/free_utils.c`

---

## 📊 Complete Data Flow Diagram

```
┌─────────────────────────────────────────────────────────┐
│                     PROGRAM START                       │
│  main() → Validate args → Load map → Validate → Init   │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                   INITIALIZATION                        │
│  MLX → Window → Camera → Textures → Hooks → Cutscene   │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                   INTRO CUTSCENE                        │
│         Show intro-louis.xpm (3s) → Press ENTER         │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                     GAME LOOP                           │
│  ┌───────────────────────────────────────────────────┐  │
│  │  update_animation() ──────────────────────┐       │  │
│  │     ↓                                     │       │  │
│  │  Update sprites → render_map()            │       │  │
│  │     ↓                ↓                    │       │  │
│  │  Draw tiles → Draw player → Draw HUD      │       │  │
│  │                                            │       │  │
│  │  handle_keypress() ────────────────────┐  │       │  │
│  │     ↓                                  │  │       │  │
│  │  Move player? → Update state → Render │  │       │  │
│  │                                        │  │       │  │
│  └────────────────────────────────────────┼──┼───────┘  │
│                                           │  │          │
│  Collect all items? ──────────────────────┘  │          │
│         │                                    │          │
│         YES                                  NO         │
│         ↓                                    ↓          │
│    Go to Exit? ──────────────────────────► Continue    │
│         │                                    │          │
│         YES                                  │          │
│         ↓                                    │          │
│    Victory Scene ◄───────────────────────────┘          │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                 VICTORY CUTSCENE                        │
│   Show to-be-continued.xpm (2s) → Auto-close           │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                    CLEANUP & EXIT                       │
│  Free textures → Destroy window → Free map → exit(0)   │
└─────────────────────────────────────────────────────────┘
```

---

## 🔑 Key Concepts Summary

### Game States
1. **Scene Mode** (`game->scene = 1`)
   - Intro cutscene
   - Victory cutscene
   - No player control

2. **Play Mode** (`game->scene = 0`)
   - Normal gameplay
   - Player can move
   - Animations active

### Movement Rules
- ✅ Can walk on: `0`, `P`, `C`, `E`
- ❌ Cannot walk on: `1` (walls), `F` (platforms), `G` (ground), `R` (roof)
- Special: Must collect all `C` before exiting at `E`

### Rendering Optimization
- Only draws visible tiles (camera viewport)
- Double buffering (render to image, then display)
- Transparent sprite system (skip 0xFF00FF color)

### Memory Management
- All textures loaded once at start
- Map grid freed on exit
- MLX properly destroyed
- **0 memory leaks** ✅

---

## 📁 File Organization

```
src/
├── so_long.c          → Main entry point
├── game_init.c        → Initialization
├── events.c           → Keyboard & movement
├── events_animation.c → Animation loop
├── scenes.c           → Cutscene system
├── render.c           → Main rendering
├── render_tiles.c     → Tile drawing
├── render_utils.c     → Sprite utilities
├── camera.c           → Viewport system
├── texture_loader.c   → Load sprites
├── map_parser.c       → Read map file
├── map_validator.c    → Validate map
├── map_count.c        → Count elements
├── pathfinding.c      → Flood fill
├── free_textures.c    → Free sprites
├── free_utils.c       → Cleanup & exit
└── error_handler.c    → Error messages
```

---

## 🎓 Learning Points

This project demonstrates:
1. **Event-driven programming** with MLX
2. **Double buffering** for smooth rendering
3. **Viewport/camera system** for large maps
4. **Sprite animation** with frame timing
5. **Flood fill algorithm** for pathfinding
6. **Memory management** (no leaks)
7. **Norminette compliance** (42 coding standards)
8. **Modular code** (separate concerns)

---

**Total Project Statistics:**
- 📄 18 source files
- 🎨 50+ sprite files
- ⚡ 0 memory leaks
- ✅ 100% norminette compliant
- 🎮 Full bonus features implemented

---

Made with 🧀 by Louis & Ozzy 🐱
