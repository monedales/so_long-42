#  SO LONG 👾

> *A 2D top-down adventure game where Louis the cat must collect all the cheese and escape from his rival Ozzy!*

[![42 School Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)](https://github.com/42School/norminette)


## Description 📜

**so_long** is a 2D game built from scratch with the **MiniLibX** graphics library. The player controls Louis (a cat 🐱) who must collect all the cheese on the map and reach the exit while avoiding walls, platforms, and Ozzy, a rival cat who patrols the map and chases Louis down on sight.

Beyond the base 42 requirements, the game features animated sprites (idle, walking, and collecting animations in all four directions), a scrolling camera that follows the player across maps larger than the window, layered map tiles (walls, floors, platforms, and roofs) for verticality, multiple enemies with collision detection, and intro/victory cutscenes.

The game also validates map format on load, ensures there's a valid path to every piece of cheese and the exit before starting, and tracks the player's move count.

### Project Goals 🎯
- Build a complete 2D game loop from scratch in C
- Practice event handling (keyboard input) and animation timing
- Work with a low-level graphics library (MiniLibX)
- Implement pathfinding algorithms (flood fill) for map validation
- Handle memory management properly (no leaks)

---

## Technologies & Concepts 🛠️

- **Language**: C
- **Graphics**: MiniLibX (X11/XQuartz)
- **Build System**: Makefile (macOS and Linux)
- **Libraries**: Custom `libft`
- **Algorithms**: Flood Fill (DFS) for path validation
- **Standards**: 42 Norminette compliant

---

## Source Code Structure 📂

```
so_long/
├── src/
│   ├── so_long.c            # Main entry point
│   ├── map_parser.c         # Map file loading
│   ├── map_validator.c      # Map format validation
│   ├── map_count.c          # Element counting (P, E, C, M)
│   ├── pathfinding.c        # Flood fill path validation
│   ├── game_init.c          # Game state initialization
│   ├── texture_loader.c     # Sprite/texture loading
│   ├── render.c             # Main render loop
│   ├── render_tiles.c       # Tile rendering (walls, floor, roof, platform)
│   ├── render_utils.c       # Rendering helpers
│   ├── camera.c             # Scrolling camera logic
│   ├── events.c             # Keyboard input and movement
│   ├── events_animation.c   # Player animation state machine
│   ├── ozzy.c                # Enemy (Ozzy) parsing, patrol, and collision
│   ├── scenes.c             # Intro/victory cutscenes
│   ├── free_textures.c      # Texture cleanup
│   ├── free_utils.c         # General memory cleanup
│   ├── file_utils.c         # File helpers
│   └── error_handler.c      # Error handling
├── include/
│   └── so_long.h            # Header file
├── maps/
│   ├── test.ber              # ✅ Valid map example
│   ├── bad_chars.ber         # ❌ Invalid characters
│   ├── bad_shape.ber         # ❌ Not rectangular
│   ├── no_path.ber           # ❌ No valid path
│   ├── open_side.ber         # ❌ Open wall (side)
│   └── open_top.ber          # ❌ Open wall (top)
├── libs/
│   ├── libft/                # Custom C library
│   └── minilibix-linux/      # MiniLibX
├── assets/                   # Game sprites and cutscene images
├── Makefile
└── README.md
```

---

## Installation & Usage ⚙️

### Prerequisites

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

#### macOS
```bash
# XQuartz is required
brew install --cask xquartz
```

> **Windows** is not supported natively (MiniLibX depends on X11). Windows users can run the Linux build inside WSL.

### Building the Project 🔨

```bash
# Clone the repository
git clone https://github.com/monedales/so_long-42.git
cd so_long-42

# Compile the project
make

# Clean object files
make clean

# Full clean (remove binary)
make fclean

# Rebuild from scratch
make re
```

### Running the Game ▶️

```bash
# Run with a valid map
./so_long maps/test.ber

# Test with invalid maps (will show error messages)
./so_long maps/bad_chars.ber
./so_long maps/no_path.ber
```

### Controls 🎮

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `A` / `←` | Move left |
| `S` / `↓` | Move down |
| `D` / `→` | Move right |
| `ESC` | Exit game |

---

## Map Format

### Valid Map Rules

1. **File extension**: Must be `.ber`
2. **Rectangular**: All rows must have the same length
3. **Core characters**:
   - `0` - Empty space
   - `1` - Wall
   - `C` - Cheese (collectible)
   - `E` - Exit
   - `P` - Player starting position
   - `M` - Enemy (Ozzy) starting position
   - `F` / `G` / `R` - Platform / floor / roof tiles, used for layered, vertical map design
4. **Required elements**:
   - Exactly **1** player (`P`)
   - Exactly **1** exit (`E`)
   - At least **1** cheese (`C`)
5. **Walls**: Map must be surrounded by walls (`1`)
6. **Valid path**: Player must be able to reach all cheese and the exit

### Example Maps

#### Valid Map (`maps/test.ber`) ✅
```
1111
1PE1
1C01
1111
```

#### Invalid: No Valid Path (`maps/no_path.ber`) ❌
```
111111
1P0E01
111111
10C001
111111
```
*The cheese `C` is unreachable.*

#### Invalid: Open Wall (`maps/open_top.ber`) ❌
```
1011
1P01
1C01
111E
```
*Top wall is not closed.*

---

## Testing 🧪

The project includes several test maps in the `maps/` directory:

| Map | Description | Expected Result |
|-----|-------------|-----------------|
| `test.ber` | Valid small map | ✅ Runs successfully |
| `bad_chars.ber` | Contains invalid character `Z` | ❌ Error: Invalid characters |
| `bad_shape.ber` | Not rectangular | ❌ Error: Map not rectangular |
| `no_path.ber` | Cheese unreachable | ❌ Error: No valid path |
| `open_side.ber` | Wall not closed (right) | ❌ Error: Walls not closed |
| `open_top.ber` | Wall not closed (top) | ❌ Error: Walls not closed |

---

## 📝 Error Messages

The game validates maps and shows clear error messages:

```bash
Error
Invalid arguments. Usage: ./so_long <map.ber>

Error
File must have .ber extension

Error
Map is not rectangular

Error
Map contains invalid characters

Error
Walls are not properly closed

Error
Invalid element count (need 1P, 1E, >=1C)

Error
No valid path to all cheese and exit
```

---

## 🎨 Game Features

### Core
- ✅ Map parsing and validation
- ✅ Rectangular map check
- ✅ Wall boundary validation
- ✅ Element count validation (P, E, C)
- ✅ Path validation (flood fill algorithm)
- ✅ Error handling with descriptive messages
- ✅ Sprite rendering
- ✅ Player movement (keyboard input, 4 directions)
- ✅ Animated player sprites (idle, walking, collecting)
- ✅ Cheese collection
- ✅ Exit mechanism
- ✅ Move counter

### Bonus
- ✅ Enemy (Ozzy): patrol behavior and collision detection with the player
- ✅ Scrolling camera for maps larger than the window
- ✅ Layered map tiles (platform, floor, roof) for vertical map design
- ✅ Intro and victory cutscenes

---

## 📚 Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Cursus - so_long](https://github.com/42cursus)
- [Flood Fill Algorithm](https://en.wikipedia.org/wiki/Flood_fill)

---

## 📄 License

This project is part of the 42 School curriculum and follows their academic policies.

---

## 🎉 Acknowledgments

- **Louis & Ozzy** 🐱🐱 - The real stars of the game (my babies!)

---

*Made with 💜 and lots of ☕ at 42 School*
