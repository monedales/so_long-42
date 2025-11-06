# 🎨 FASE 2 Preparation - Visual Assets Guide

## 🎯 What You Need for Rendering

FASE 2 is about **bringing your map to life** with graphics! Here's everything you need to prepare.

---

## 📦 Required Assets

### Minimum Required Sprites (5 types):

1. **🧱 Wall** (`1`) - The barriers
2. **⬜ Floor** (`0`) - Empty walkable space  
3. **💎 Collectible** (`C`) - Items to collect
4. **🚪 Exit** (`E`) - The goal/door
5. **🐱 Player** (`P`) - Louis the cat

### Recommended Sizes:

**For 42 School (typical):**
- **64x64 pixels** - Standard, works well
- **32x32 pixels** - Smaller, fits more on screen
- **128x128 pixels** - Larger, more detailed

**Pick ONE size and use it for ALL sprites** (consistency!)

---

## 🎨 Asset Options

### Option 1: Create Your Own! 🎨

**Tools:**
- **Pixaki** (iPad) - Great for pixel art
- **Aseprite** (Mac/PC) - Professional pixel editor ($20)
- **Piskel** (Web, Free) - Online pixel art editor
- **GIMP** (Free) - General image editor

**Tips for beginners:**
```
1. Start with 32x32 or 64x64 canvas
2. Use a limited color palette (4-8 colors)
3. Keep it simple - even solid colors work!
4. Save as PNG or XPM format
```

**Simple color scheme example:**
- Wall: Gray/Brown (#8B4513)
- Floor: Light beige (#F5DEB3)
- Collectible: Gold/Yellow (#FFD700)
- Exit: Green (#00FF00)
- Player: Blue/Orange (your choice!)

---

### Option 2: Use Free Assets 🎁

**Where to find:**

1. **OpenGameArt.org**
   - Search: "top down tileset"
   - License: Usually CC0 (free)

2. **Itch.io**
   - Search: "free pixel art"
   - Many free asset packs

3. **Kenney.nl**
   - Tons of free game assets
   - Very permissive license

4. **Pixilart.com**
   - Community sprites
   - Check licenses!

**⚠️ Important:** Always check the license! Credit the artist if required.

---

### Option 3: Use Placeholder Colors 🟦

**Fastest option** - Use colored squares while you code:

```c
// Create colored rectangles in code
mlx_put_pixel(img, x, y, 0x8B4513);  // Brown wall
mlx_put_pixel(img, x, y, 0xF5DEB3);  // Beige floor
mlx_put_pixel(img, x, y, 0xFFD700);  // Gold collectible
mlx_put_pixel(img, x, y, 0x00FF00);  // Green exit
mlx_put_pixel(img, x, y, 0x0000FF);  // Blue player
```

**Advantage:** Start coding immediately, add real sprites later!

---

## 🗂️ Asset Organization

### Recommended Folder Structure:

```
so_long/
├── assets/
│   ├── sprites/
│   │   ├── wall.xpm         (or .png)
│   │   ├── floor.xpm
│   │   ├── collectible.xpm
│   │   ├── exit.xpm
│   │   └── player.xpm
│   └── animations/          (optional, for bonus)
│       ├── player_walk/
│       └── collectible_spin/
├── src/
├── include/
└── maps/
```

---

## 📋 File Formats

### XPM (Recommended for 42)

**Pros:**
- ✅ Native MinilibX support
- ✅ Easy to create
- ✅ Text-based (can edit in vim!)
- ✅ Built-in transparency

**Example 4x4 wall.xpm:**
```c
/* XPM */
static char *wall_xpm[] = {
"4 4 2 1",
"# c #8B4513",
". c None",
"####",
"####",
"####",
"####"
};
```

**How to create:**
1. Draw in any editor
2. Export as XPM
3. Or use online XPM creator

### PNG (Alternative)

**Pros:**
- ✅ More editors support it
- ✅ Better quality/compression
- ✅ Standard format

**Cons:**
- ❌ Need `mlx_png_file_to_image()` (check if available)
- ❌ Less portable

---

## 🎮 Louis & Ozzy Theme Assets

Since your project is **Louis vs Ozzy** (cats! 🐱), here are theme ideas:

### For Louis (Player):
```
Simple cat sprite (32x32):
  /\_/\
 ( o.o )
  > ^ <

Colors:
- Orange/ginger cat
- Blue eyes
- White paws
```

### For Ozzy (Enemy - Bonus):
```
Different cat (32x32):
  /\_/\
 ( -.- )  ← Sleeping/grumpy face
  > ^ <

Colors:
- Gray/black cat
- Green eyes
- Pink nose
```

### Collectibles (Cat themed):
- 🐟 Fish
- 🧶 Yarn ball
- 🐭 Toy mouse
- ⭐ Cat treats

### Exit:
- 🚪 Cat door
- 🏠 Cat house
- 🛏️ Cat bed

---

## 🖼️ Quick Start Template

### Minimal Set (5 sprites, solid colors):

Create these in any image editor at 64x64:

1. **wall.xpm** - Brown square (#8B4513)
2. **floor.xpm** - Beige square (#F5DEB3)
3. **coin.xpm** - Yellow circle (#FFD700)
4. **exit.xpm** - Green square with arrow (#00FF00)
5. **player.xpm** - Orange cat shape or square (#FF8C00)

**Time estimate:** 30 minutes for all 5!

---

## 💻 Code Preparation

### Create Image Loading Function:

```c
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

t_img	load_image(void *mlx, char *path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.img)
	{
		ft_printf("Error loading: %s\n", path);
		exit(1);
	}
	return (img);
}
```

### Load All Sprites:

```c
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	wall;
	t_img	floor;
	t_img	collectible;
	t_img	exit;
	t_img	player;
}	t_game;

void	load_sprites(t_game *game)
{
	game->wall = load_image(game->mlx, "assets/sprites/wall.xpm");
	game->floor = load_image(game->mlx, "assets/sprites/floor.xpm");
	game->collectible = load_image(game->mlx, "assets/sprites/coin.xpm");
	game->exit = load_image(game->mlx, "assets/sprites/exit.xpm");
	game->player = load_image(game->mlx, "assets/sprites/player.xpm");
}
```

---

## ✅ Pre-FASE 2 Checklist

Before you start coding rendering:

### Assets:
- [ ] Decided on sprite size (32x32, 64x64, etc.)
- [ ] Created or found 5 basic sprites
- [ ] Saved in correct format (XPM or PNG)
- [ ] Organized in `assets/sprites/` folder
- [ ] Tested loading one sprite with MinilibX

### Code Structure:
- [ ] Know how to call `mlx_xpm_file_to_image()`
- [ ] Know how to call `mlx_put_image_to_window()`
- [ ] Understand tile-based rendering concept
- [ ] Have a plan for game struct (t_game)

### Understanding:
- [ ] Know what a tile is (one grid cell = one sprite)
- [ ] Understand coordinate mapping (map[y][x] → screen x,y)
- [ ] Know sprite size × map position = screen position

---

## 🎨 Rendering Concept Preview

**Map to Screen Mapping:**

```
Map:          Screen (if tile_size = 64):
1 1 1         0,0    64,0   128,0
1 P 0    →    0,64   64,64  128,64
1 1 1         0,128  64,128 128,128

Formula:
screen_x = map_x * TILE_SIZE
screen_y = map_y * TILE_SIZE
```

---

## 🚀 Recommended Approach

### Day 1 - Get ONE sprite working:
1. Create a simple 64x64 wall.xpm (brown square)
2. Open a window
3. Load the sprite
4. Draw it at position (0, 0)
5. Celebrate! 🎉

### Day 2 - Render full map:
1. Loop through map array
2. For each cell, draw appropriate sprite
3. Handle all 5 types (0,1,C,E,P)

### Day 3 - Polish:
1. Add animations (optional)
2. Fix visual bugs
3. Test different maps

---

## 📚 Resources

### MiniLibX Functions You'll Need:

```c
// Initialize
void	*mlx_init(void);
void	*mlx_new_window(void *mlx, int w, int h, char *title);

// Load image
void	*mlx_xpm_file_to_image(void *mlx, char *path, int *w, int *h);

// Display image
int		mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);

// Cleanup
int		mlx_destroy_image(void *mlx, void *img);
int		mlx_destroy_window(void *mlx, void *win);
```

### Helpful Links:

- **MiniLibX Docs:** (42 Intranet)
- **XPM Format:** [Wikipedia - XPM](https://en.wikipedia.org/wiki/X_PixMap)
- **Free Pixel Art:** [Kenney.nl](https://kenney.nl/)

---

## 🎯 Final Recommendation

**For your first time:**

1. **Start simple** - Use colored squares or very basic sprites
2. **Get it working** - Ugly but functional is better than pretty but broken
3. **Iterate** - Replace placeholders with nice sprites later
4. **Have fun!** - Your cats Louis & Ozzy deserve cute sprites! 🐱

**Time estimate for basic visuals:** 2-3 hours  
**Time for polished sprites:** 1-2 days (if creating from scratch)

---

## 💡 Pro Tips

1. **Use transparent backgrounds** - XPM supports it with `None` color
2. **Keep aspect ratio 1:1** - Square sprites are easiest
3. **Test on small map first** - Don't debug on a 50x50 map!
4. **Use defines for colors** - `#define WALL_COLOR 0x8B4513`
5. **Create a sprite loading function** - Don't repeat code!

---

Ready to make your game beautiful? Start with one sprite and build from there! 🚀🎨

**Next file to read:** `rendering_basics.md` (coming next!)
