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
    ├─ trim_newline() → Remove \n
    ├─ ft_append_line() → Add to char **grid
    ├─ Free line after appending
    └─ Return grid
```

**File:** `src/map_parser.c`

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
- `ERR_NOT_RECTANG` - Not rectangular
- `ERR_NOT_WALLS` - Missing border walls
- `ERR_ELEM_INVALID` - No player/exit or wrong count
- `ERR_CHARS_INVALID` - Invalid characters
- `ERR_NO_PATH` - No valid path to collectibles/exit

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

### Understanding mlx_loop()

O `mlx_loop(game.mlx)` é o **coração do jogo** - um loop infinito que mantém o programa rodando até chamarmos `exit()`.

**Como funciona:**
```c
int main(int argc, char **argv)
{
    // ... validação e inicialização ...
    
    init_game(&game);  // ← Registra os hooks aqui
    mlx_loop(game.mlx); // ← Entra no loop infinito
    
    return (0);  // ← Nunca chega aqui (exit() é chamado antes)
}
```

### Hooks (Event Callbacks)

Durante `init_game()`, registramos 3 **hooks** (funções que o MiniLibX chama automaticamente):

```c
void init_game(t_game *game)
{
    // ... inicialização ...
    
    // Hook 1: Fechar janela (evento 17 do X11)
    mlx_hook(game->win, 17, 0, handle_close, game);
    
    // Hook 2: Teclado (qualquer tecla pressionada)
    mlx_key_hook(game->win, handle_keypress, game);
    
    // Hook 3: Loop contínuo (chamado a cada frame)
    mlx_loop_hook(game->mlx, update_animation, game);
}
```

### Main Loop (mlx_loop) - Anatomia

```
mlx_loop(game.mlx)  ← LOOP INFINITO
    │
    ├─────────────────────────────────────────────────
    │  CADA ITERAÇÃO DO LOOP (60+ vezes por segundo):
    │
    ├─ [1] Processa eventos do X11
    │      (movimento do mouse, redraw, etc.)
    │
    ├─ [2] Chama mlx_loop_hook automaticamente
    │      └─→ update_animation(game)
    │          ├─ Incrementa contadores
    │          ├─ Atualiza frame de animações
    │          └─ Chama render_map() se necessário
    │
    ├─ [3] Se tecla foi pressionada:
    │      └─→ handle_keypress(keycode, game)
    │          ├─ ESC → close_game() → exit(0) → SAI DO LOOP ✗
    │          ├─ ENTER (se scene mode) → avança cutscene
    │          └─ WASD/Arrows → move_player()
    │
    ├─ [4] Se clicou botão [X] da janela:
    │      └─→ handle_close(game)
    │          └─ close_game() → exit(0) → SAI DO LOOP ✗
    │
    └─ Volta para o início do loop ↻
       (continua até exit() ser chamado)
```

**IMPORTANTE:** O loop só termina quando chamamos `exit(0)` dentro de `close_game()`!

### Animation Update (every frame)
```
update_animation(game)  ← Chamado automaticamente pelo mlx_loop_hook
    │
    ├─ Incrementa contadores globais:
    │   ├─ player.anim_counter++  (para idle animation)
    │   └─ cheese_counter++       (para cheese animation)
    │
    ├─ Update Player Idle Animation:
    │   ├─ Se player.anim_counter >= IDLE_WAIT (300000):
    │   │   └─ A cada ANIM_DELAY frames (5000):
    │   │       ├─ player.frame = (frame + 1) % IDLE_FRAMES
    │   │       └─ render_map() se frame mudou
    │   └─ (Tail wagging effect quando parado)
    │
    ├─ Update Cheese Animation:
    │   └─ A cada CHEESE_DELAY frames (20000):
    │       ├─ cheese_frame = (frame + 1) % 5
    │       └─ render_map() se frame mudou
    │
    └─ Update Collecting Animation:
        └─ Se player.is_collecting:
            ├─ collect_counter++
            └─ Se counter >= COLLECT_DURATION:
                └─ is_collecting = 0
```

**Files:** `src/events_animation.c`

**Timing Values:**
- `ANIM_DELAY = 5000` - Walk/idle animation speed
- `IDLE_WAIT = 300000` - Time before idle animation starts
- `CHEESE_DELAY = 20000` - Cheese rotation speed
- `COLLECT_DURATION = 15000` - Collection animation duration

---

## ⌨️ Event Handling

### Keyboard Input Flow
```
handle_keypress(keycode, game)  ← Chamado quando qualquer tecla é pressionada
    │
    ├─ [PRIORITY 1] ESC Key:
    │   └─ close_game() → Cleanup → exit(0)
    │
    ├─ [PRIORITY 2] Scene Mode (game->scene == 1):
    │   └─ If keycode == ENTER:
    │       ├─ game->scene_id++
    │       ├─ handle_scenes() → Next cutscene
    │       └─ return (block other inputs)
    │
    └─ [PRIORITY 3] Play Mode (game->scene == 0):
        └─ Movement keys (WASD/Arrows) → Process movement
```

**File:** `src/events.c`

### Movement Processing
```
handle_keypress(keycode, game)  ← Processa movimento do jogador
    │
    ├─ Step 1: Calculate new position
    │   └─ process_movement(keycode, &new_x, &new_y, game)
    │       ├─ W/UP    → new_y--, direction = DIR_BACK
    │       ├─ S/DOWN  → new_y++, direction = DIR_FRONT
    │       ├─ A/LEFT  → new_x--, direction = DIR_LEFT
    │       └─ D/RIGHT → new_x++, direction = DIR_RIGHT
    │
    ├─ Step 2: Update animation direction
    │   └─ update_back_anim(game, keycode)
    │       └─ Se tecla W/UP: alterna frame (paw animation)
    │
    ├─ Step 3: Validate move
    │   └─ is_valid_move(game, new_x, new_y)
    │       ├─ Check boundaries (0 <= x < width, 0 <= y < height)
    │       ├─ Check walls: '1' = blocked ❌
    │       ├─ Check platforms: 'F' = blocked ❌
    │       ├─ Check floor: 'G' = blocked ❌
    │       ├─ Check roof: 'R' = blocked ❌
    │       └─ Valid tiles: '0', 'P', 'C', 'E' = can walk ✅
    │
    └─ Step 4: Execute move (if valid)
        └─ move_player(game, new_x, new_y)
            [See Player Movement Logic below]
```

### Player Movement Logic
```
move_player(game, new_x, new_y)
    │
    ├─ Step 1: Check collectible
    │   └─ If map[new_y][new_x] == 'C':
    │       ├─ game->map.collected++
    │       ├─ player.is_collecting = 1
    │       └─ map[new_y][new_x] = '0'  (remove from map)
    │
    ├─ Step 2: Check victory condition
    │   └─ If map[new_y][new_x] == 'E' AND collected == collectibles:
    │       ├─ update_map_grid(game, new_x, new_y)
    │       ├─ game->map.player_pos = (new_x, new_y)
    │       ├─ game->moves++
    │       ├─ render_map() → Draw final state
    │       ├─ trigger_victory_scene()
    │       │   ├─ game->scene = 1
    │       │   ├─ game->scene_id = 10
    │       │   └─ handle_scenes() → Victory cutscene
    │       └─ return
    │
    ├─ Step 3: Update map grid
    │   └─ update_map_grid(game, new_x, new_y)
    │       ├─ If old_pos == exit_pos: restore 'E'
    │       ├─ Else: set old_pos to '0'
    │       └─ Set new_pos to 'P'
    │
    ├─ Step 4: Update player state
    │   ├─ game->map.player_pos.x = new_x
    │   ├─ game->map.player_pos.y = new_y
    │   ├─ game->moves++
    │   └─ game->player.walk_frame++
    │
    ├─ Step 5: Print to terminal
    │   └─ ft_printf("Moves: %d\n", game->moves)
    │
    └─ Step 6: Render update
        └─ render_map()
            [See Rendering Pipeline below]
```

**Special Cases:**
- Can walk over 'E' (exit) without all collectibles
- Exit tile is preserved when leaving it
- Player position always marked as 'P' in grid

### Victory Trigger
```
trigger_victory_scene(game)  ← Chamado quando player chega no exit com tudo coletado
    │
    ├─ game->scene = 1        (ativa modo cutscene)
    ├─ game->scene_id = 10    (ID da vitória)
    └─ handle_scenes()
        │
        └─ If scene_id == 10:
            ├─ show_scene("assets/scenes/to-be-continued.xpm")
            │   ├─ mlx_xpm_file_to_image() → Load image
            │   ├─ mlx_put_image_to_window() → Display
            │   ├─ mlx_do_sync() → Force update
            │   └─ mlx_destroy_image() → Free image
            │
            ├─ my_usleep(3.0)  ← Busy-wait 3 seconds
            │   └─ while (get_time() - start < 3.0)
            │       └─ Loop (no usleep allowed by 42)
            │
            ├─ ft_printf("\n🎉 WEERK! YOU WIN! 🎉\n")
            ├─ ft_printf("Moves: %d\n", game->moves)
            │
            └─ close_game(game)
                └─ [See Game End section]
```

**File:** `src/scenes.c`

---

## 🎨 Rendering Pipeline

### Complete Render Flow
```
render_map(game)  ← Chamado sempre que precisa redesenhar a tela
    │
    ├─ Step 1: Render Gradient Background
    │   └─ render_gradient_background(game)
    │       ├─ Fill frame buffer pixel by pixel
    │       ├─ Vertical gradient: white (top) → light gray (bottom)
    │       ├─ gray = 255 - (y * 55 / height)
    │       └─ color = (gray << 16) | (gray << 8) | gray
    │
    ├─ Step 2: Update Camera Position
    │   └─ update_camera(game)
    │       ├─ target_x = player_x - (camera_width / 2)
    │       ├─ target_y = player_y - (camera_height / 2)
    │       ├─ Clamp to boundaries (0 to max_x/max_y)
    │       └─ Store camera.x, camera.y (in tiles, not pixels)
    │
    ├─ Step 3: Iterate Through Visible Tiles
    │   └─ For y from camera.y to camera.y + camera.height:
    │       └─ For x from camera.x to camera.x + camera.width:
    │           └─ render_cell(game, x, y)
    │
    ├─ Step 4: Render Each Cell (render_cell)
    │   └─ Based on map.grid[y][x]:
    │       ├─ If '1' → render_tile(&game->wall)
    │       │   └─ Centered in cell (offset = (64 - width) / 2)
    │       │
    │       ├─ If 'R' → render_roof(&game->roof)
    │       │   ├─ Horizontally centered
    │       │   └─ Vertically aligned to TOP (offset_y = 0)
    │       │
    │       ├─ If 'G' → render_tile(&game->floor)
    │       │   └─ Centered in cell
    │       │
    │       ├─ If 'F' → render_sprite_centered(&game->platform)
    │       │   └─ Centered with transparency support
    │       │
    │       ├─ If 'C' → render_sprite_centered(&game->cheese[frame])
    │       │   └─ Animated cheese (frame 0-4)
    │       │
    │       ├─ If 'E' → render_sprite_centered(&game->exit)
    │       │   └─ Exit door sprite
    │       │
    │       └─ If 'P' → get_player_sprite() → render_sprite_centered()
    │           └─ [See Player Sprite Selection below]
    │
    ├─ Step 5: Handle Special Case - Player on Exit
    │   └─ render_player_on_exit(game, x, y)
    │       └─ If player_pos == exit_pos == current_cell:
    │           ├─ Draw exit sprite first
    │           └─ Draw player sprite on top (proper layering)
    │
    ├─ Step 6: Display Frame Buffer
    │   └─ mlx_put_image_to_window(game->frame.img)
    │       └─ Copy entire frame buffer to window (double buffering)
    │
    └─ Step 7: Overlay Move Counter
        └─ render_move_counter(game)
            ├─ Create text: "Moves: " + ft_itoa(moves)
            ├─ Draw black outline (3x3 grid around text)
            │   └─ 8 shadows at offsets (-2 to +2) in black
            ├─ Draw main text in gold (0xFFD700) at (13, 23)
            └─ Free allocated strings
```

**Files:**
- `src/render.c` - Main rendering orchestration
- `src/render_tiles.c` - Tile & sprite positioning
- `src/render_utils.c` - Low-level pixel operations
- `src/camera.c` - Viewport calculations

### Player Sprite Selection
```
get_player_sprite(game)  ← Determina qual sprite do jogador usar
    │
    ├─ Priority 1: Collecting Animation
    │   └─ If is_collecting: return &player.collect
    │
    ├─ Priority 2: Idle Animation (tail wag)
    │   └─ If anim_counter >= IDLE_WAIT (300000):
    │       └─ return &player.back[frame]  (cycles 0-1)
    │
    ├─ Priority 3: Directional Sprites
    │   ├─ DIR_BACK:
    │   │   └─ return &player.back[frame]
    │   │
    │   ├─ DIR_LEFT:
    │   │   ├─ If walk_frame % 2 == 0: return &player.left
    │   │   └─ Else: return &player.left_paw
    │   │
    │   ├─ DIR_RIGHT:
    │   │   ├─ If walk_frame % 2 == 0: return &player.right
    │   │   └─ Else: return &player.right_paw
    │   │
    │   └─ DIR_FRONT (default):
    │       ├─ If moves == 0: return &player.front (initial state)
    │       ├─ If walk_frame % 2 == 0: return &player.front_paw
    │       └─ Else: return &player.front_paw_mirror
```

### Camera Viewport System
```
init_camera(game)  ← Inicialização única no setup
    │
    ├─ Calculate viewport dimensions (in tiles):
    │   ├─ camera.width = frame.width / tile_size
    │   └─ camera.height = frame.height / tile_size
    │
    ├─ Calculate maximum camera position:
    │   ├─ camera.max_x = map.width - camera.width
    │   ├─ camera.max_y = map.height - camera.height
    │   └─ If max < 0: set to 0 (map smaller than viewport)
    │
    └─ Initialize position at (0, 0)

update_camera(game)  ← Chamado todo frame antes de renderizar
    │
    ├─ Calculate target position (center on player):
    │   ├─ target_x = player_x - (camera_width / 2)
    │   └─ target_y = player_y - (camera_height / 2)
    │
    ├─ Clamp to boundaries:
    │   ├─ If target_x < 0: target_x = 0
    │   ├─ If target_y < 0: target_y = 0
    │   ├─ If target_x > max_x: target_x = max_x
    │   └─ If target_y > max_y: target_y = max_y
    │
    └─ Update camera.x and camera.y

Note: Camera positions are in TILES (grid coordinates), not pixels!
```

### Sprite Rendering Functions
```
render_tile(game, x, y, sprite)  ← Para tiles opacos (wall, floor)
    │
    ├─ Calculate centering offset:
    │   ├─ offset_x = (tile_size - sprite.width) / 2
    │   └─ offset_y = (tile_size - sprite.height) / 2
    │
    ├─ Convert grid position to screen position:
    │   ├─ screen_x = (x - camera.x) * tile_size + offset_x
    │   └─ screen_y = (y - camera.y) * tile_size + offset_y
    │
    └─ draw_sprite_to_frame(frame, sprite, screen_x, screen_y)
        └─ Copy sprite with transparency check

render_roof(game, sprite, x, y)  ← Para tetos (alinhado ao topo)
    │
    ├─ Horizontally centered:
    │   └─ offset_x = (tile_size - sprite.width) / 2
    │
    ├─ Vertically aligned to TOP (no offset_y):
    │   ├─ screen_x = (x - camera.x) * tile_size + offset_x
    │   └─ screen_y = (y - camera.y) * tile_size + 0
    │
    └─ draw_sprite_to_frame(frame, sprite, screen_x, screen_y)

render_sprite_centered(game, sprite, x, y)  ← Para objetos transparentes
    │
    ├─ Center both horizontally and vertically:
    │   ├─ offset_x = (tile_size - sprite.width) / 2
    │   └─ offset_y = (tile_size - sprite.height) / 2
    │
    ├─ Convert to screen position:
    │   ├─ screen_x = (x - camera.x) * tile_size + offset_x
    │   └─ screen_y = (y - camera.y) * tile_size + offset_y
    │
    └─ draw_sprite_to_frame(frame, sprite, screen_x, screen_y)
        └─ Skip pixels with color == 0xFF00FF (magenta = transparent)
```

### Low-Level Pixel Operations
```
draw_sprite_to_frame(frame, sprite, px, py)  ← Com transparência
    │
    └─ For each pixel in sprite:
        ├─ color = get_pixel_color(sprite, x, y)
        ├─ If color != TRANSPARENT_COLOR (0xFF00FF):
        │   └─ put_pixel(frame, px + x, py + y, color)
        └─ Skip transparent pixels (background shows through)

put_pixel(frame, x, y, color)  ← Escreve pixel no frame buffer
    │
    ├─ Boundary check (skip if outside frame)
    ├─ Calculate address:
    │   └─ dst = addr + (y * line_len + x * (bpp / 8))
    └─ Write: *(unsigned int *)dst = color

get_pixel_color(sprite, x, y)  ← Lê cor de um sprite
    │
    ├─ Boundary check (return TRANSPARENT_COLOR if outside)
    ├─ Calculate address:
    │   └─ src = addr + (y * line_len + x * (bpp / 8))
    └─ return *(int *)src
```

### Move Counter Display (HUD)
```
render_move_counter(game)  ← Overlay de texto sobre o frame
    │
    ├─ Create strings:
    │   ├─ moves_str = ft_itoa(game->moves)
    │   └─ counter_text = ft_strjoin("Moves: ", moves_str)
    │
    ├─ Draw black outline (shadow effect):
    │   └─ 3x3 grid (i: -2 to +2, j: -2 to +2):
    │       └─ mlx_string_put(13 + i, 23 + j, 0x000000)
    │           └─ Skip center (0, 0) - where main text goes
    │
    ├─ Draw main text:
    │   └─ mlx_string_put(13, 23, 0xFFD700)  ← Gold color
    │
    └─ Free memory:
        ├─ free(moves_str)
        └─ free(counter_text)

Note: mlx_string_put draws directly on window, NOT on frame buffer!
This is why it's called AFTER mlx_put_image_to_window.
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
│  MLX → Parse dimensions → Parse data → Window →        │
│  Camera → Textures → Scene setup (scene=1, id=0) →     │
│  Hooks (close, keypress, animation) → handle_scenes()  │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                   INTRO CUTSCENE                        │
│    scene_id=0: show intro-louis.xpm (3s wait)          │
│              Wait for ENTER key press                   │
│    scene_id=1: Set scene=0 → render_map() → Start game │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                     GAME LOOP                           │
│  ┌───────────────────────────────────────────────────┐  │
│  │  update_animation() (every frame)                 │  │
│  │     ├─ player.anim_counter++                      │  │
│  │     ├─ Update idle animation (if counter > WAIT)  │  │
│  │     ├─ Update cheese animation (cycle frames)     │  │
│  │     └─ render_map() if frame changed              │  │
│  │                                                    │  │
│  │  handle_keypress(keycode)                         │  │
│  │     ├─ ESC → close_game()                         │  │
│  │     ├─ If scene mode: ENTER → scene_id++          │  │
│  │     └─ If play mode (scene=0):                    │  │
│  │         ├─ process_movement() → new_x, new_y      │  │
│  │         ├─ update_back_anim() → sprite direction  │  │
│  │         ├─ is_valid_move() → check collision      │  │
│  │         └─ move_player():                         │  │
│  │             ├─ Collect 'C' → collected++          │  │
│  │             ├─ Check Exit 'E':                    │  │
│  │             │   └─ If all collected:              │  │
│  │             │       ├─ update_map_grid()          │  │
│  │             │       ├─ moves++                    │  │
│  │             │       ├─ render_map()               │  │
│  │             │       └─ trigger_victory_scene()    │  │
│  │             ├─ update_map_grid()                  │  │
│  │             ├─ moves++                            │  │
│  │             ├─ walk_frame++                       │  │
│  │             ├─ ft_printf("Moves: %d")             │  │
│  │             └─ render_map()                       │  │
│  │                 ├─ update_camera() → follow       │  │
│  │                 ├─ Draw visible tiles             │  │
│  │                 ├─ Draw player sprite             │  │
│  │                 ├─ Draw HUD (move counter)        │  │
│  │                 └─ mlx_put_image_to_window()      │  │
│  └───────────────────────────────────────────────────┘  │
└────────────────────┬────────────────────────────────────┘
                     │ (Victory triggered)
                     ▼
┌─────────────────────────────────────────────────────────┐
│                 VICTORY SEQUENCE                        │
│  trigger_victory_scene():                               │
│      ├─ Set scene=1, scene_id=10                        │
│      └─ handle_scenes():                                │
│          ├─ show_scene(to-be-continued.xpm)             │
│          ├─ my_usleep(3.0) → Busy-wait 3 seconds        │
│          ├─ ft_printf("🎉 WEERK! YOU WIN! 🎉")         │
│          ├─ ft_printf("Moves: %d")                      │
│          └─ close_game()                                │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                    CLEANUP & EXIT                       │
│  close_game():                                          │
│      ├─ free_textures() → mlx_destroy_image() all      │
│      ├─ mlx_destroy_window()                            │
│      ├─ free_map() → free grid rows + array             │
│      ├─ mlx_destroy_display()                           │
│      ├─ free(mlx)                                       │
│      └─ exit(0) → Clean termination                     │
└─────────────────────────────────────────────────────────┘

ALTERNATIVE EXITS:
  • ESC key → close_game() (same cleanup)
  • Window [X] → handle_close() → close_game()
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
├── file_utils.c       → File utilities
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
