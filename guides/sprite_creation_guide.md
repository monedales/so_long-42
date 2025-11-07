# 🎨 Sprite Creation Guide - ImageMagick Workflow

**Date:** November 7, 2025  
**Project:** so_long - Louis vs Ozzy

---

## 📋 Table of Contents
1. [Quick Reference](#quick-reference)
2. [Step-by-Step Workflow](#step-by-step-workflow)
3. [ImageMagick Commands](#imagemagick-commands)
4. [Sprite Specifications](#sprite-specifications)
5. [Troubleshooting](#troubleshooting)

---

## 🚀 Quick Reference

### Essential Commands

```bash
# Basic conversion: JPEG to XPM (80x80)
magick input.jpeg -resize 80x80 output.xpm

# With transparency (magenta background)
magick input.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm

# Crop and resize
magick input.jpeg \
  -crop WIDTHxHEIGHT+X+Y \
  -resize 80x80 \
  output.xpm

# Auto-trim and resize
magick input.jpeg \
  -trim +repage \
  -resize 80x80 \
  output.xpm
```

---

## 📝 Step-by-Step Workflow

### Workflow 1: Simple Conversion (No Transparency)

**Best for:** Tiles that fill the entire square (walls, floors)

```bash
# 1. Navigate to project directory
cd /Users/mona/Documents/42-2025/so_long

# 2. Convert JPEG to XPM
magick assets/sprites-louis/source-image.jpeg \
  -resize 64x64 \
  assets/temp/sprite-name.xpm

# 3. Test in game
make && ./so_long maps/test.ber
```

### Workflow 2: With Manual Transparency (Recommended!)

**Best for:** Character sprites (Louis, Ozzy) with backgrounds

```bash
# Step 1: Crop in Preview (macOS)
# - Open image in Preview
# - Tools → Select → Draw rectangle around cat
# - Cmd+K to crop
# - File → Export → Save as JPEG

# Step 2: Convert with ImageMagick
magick assets/sprites-louis/louis-cropped.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-front80.xpm

# Step 3: Manually edit XPM (if needed)
# Open the .xpm file in VS Code
# Find the background color line (usually first color)
# Change it to: "   c #FF00FF",
# This makes it magenta (transparent in game)

# Step 4: Test
make && ./so_long maps/test.ber
```

### Workflow 3: Batch Processing Multiple Sprites

```bash
# Create a script for all your sprites
#!/bin/bash

# Louis sprites
magick assets/sprites-louis/louis-front.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-front80.xpm

magick assets/sprites-louis/louis-back.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-back80.xpm

# Ozzy sprites
magick assets/sprites-ozzy/ozzy-front.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-ozzy/ozzy-front80.xpm

# Collectibles
magick assets/cheese/cheese.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 64x64 \
  assets/temp/cheese.xpm

# Exit
magick assets/exit/cat-furniture.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 64x64 \
  assets/temp/exit.xpm
```

---

## 🛠 ImageMagick Commands

### Basic Operations

```bash
# Resize (maintain aspect ratio)
magick input.jpeg -resize 80x80 output.xpm

# Resize (force exact dimensions, may distort)
magick input.jpeg -resize 80x80! output.xpm

# Resize (only if larger)
magick input.jpeg -resize 80x80\> output.xpm
```

### Cropping

```bash
# Crop specific region: WIDTHxHEIGHT+X_OFFSET+Y_OFFSET
magick input.jpeg -crop 500x600+100+50 output.xpm

# Auto-trim whitespace
magick input.jpeg -trim +repage output.xpm

# Crop to square (centered)
magick input.jpeg \
  -gravity center \
  -crop 1:1 +repage \
  -resize 80x80 \
  output.xpm
```

### Transparency

```bash
# Make white transparent, replace with magenta
magick input.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  output.xpm

# Make specific color transparent
magick input.jpeg \
  -fuzz 10% -transparent "#EBEBEB" \
  -background "#FF00FF" -alpha remove -alpha off \
  output.xpm

# Adjust fuzz tolerance
# -fuzz 0%   = Exact color match
# -fuzz 10%  = Similar colors
# -fuzz 20%  = More variation (recommended for photos)
# -fuzz 30%  = Very loose matching
```

### Quality & Enhancement

```bash
# Sharpen
magick input.jpeg -sharpen 0x1 -resize 80x80 output.xpm

# Enhance contrast
magick input.jpeg -contrast -resize 80x80 output.xpm

# Adjust brightness
magick input.jpeg -brightness-contrast 10x5 -resize 80x80 output.xpm

# Combine enhancements
magick input.jpeg \
  -contrast \
  -sharpen 0x1 \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm
```

### Information & Testing

```bash
# Get image info
magick identify input.jpeg

# Detailed info
magick identify -verbose input.jpeg

# Check XPM format
head -20 output.xpm

# Count colors in XPM
grep "c #" output.xpm | wc -l
```

---

## 📏 Sprite Specifications

### Current Project Settings

| Element | Size | Transparency | Notes |
|---------|------|--------------|-------|
| **Tile Size** | 64x64 | N/A | Base grid unit |
| **Player (Louis)** | 80x80 | Yes (#FF00FF) | Overlaps tiles for presence |
| **Enemy (Ozzy)** | 80x80 | Yes (#FF00FF) | Same as player |
| **Collectible (Cheese)** | 64x64 | Yes (#FF00FF) | Fits in tile |
| **Exit (Cat Furniture)** | 64x64 | Optional | Depends on design |
| **Wall** | 64x64 | No | Opaque tile |
| **Floor** | 64x64 | No | Opaque tile |

### Size Recommendations

```bash
# Perfect fit (no overlap)
-resize 64x64

# Character presence (slight overlap)
-resize 80x80

# Larger characters (more overlap)
-resize 96x96

# Small details
-resize 48x48
```

### Transparency Color

**Always use:** `#FF00FF` (Magenta)
- RGB: (255, 0, 255)
- Bright pink - easy to spot if something goes wrong
- Never appears naturally in photos
- Defined in `render_utils.c` as `TRANSPARENT_COLOR`

---

## 🎯 Recommended Sprite Workflow

### For Louis (Player)

```bash
# Front view (current)
magick assets/sprites-louis/louis-front.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-front80.xpm

# Back view
magick assets/sprites-louis/louis-back.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-back80.xpm

# Left side
magick assets/sprites-louis/louis-left.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-louis/louis-left80.xpm

# Right side (or flip left)
magick assets/sprites-louis/louis-left80.xpm \
  -flop \
  assets/sprites-louis/louis-right80.xpm
```

### For Ozzy (Enemy - Bonus)

```bash
# Same process as Louis
magick assets/sprites-ozzy/ozzy-jumping.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  assets/sprites-ozzy/ozzy-jump80.xpm
```

### For Cheese (Collectible)

```bash
# Smaller, centered in tile
magick assets/cheese/cheese.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 64x64 \
  assets/temp/cheese.xpm
```

### For Cat Furniture (Exit)

```bash
# Tile-sized, may not need transparency
magick assets/exit/cat-tree.jpeg \
  -resize 64x64 \
  assets/temp/exit.xpm

# Or with transparency if it has background
magick assets/exit/cat-tree.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 64x64 \
  assets/temp/exit.xpm
```

---

## 🔧 Troubleshooting

### Problem: Transparent parts inside the sprite

**Cause:** `-fuzz` value too high, matching colors inside the cat

**Solution:**
```bash
# Lower the fuzz value
magick input.jpeg \
  -fuzz 10% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm

# Or manually edit the XPM file
# Only change the background color definition to #FF00FF
```

### Problem: White/black background still showing

**Cause:** Didn't use transparency or wrong color

**Solution:**
```bash
# Make sure to include all transparency flags
magick input.jpeg \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm

# Then verify in XPM file that background color is:
"   c #FF00FF",
```

### Problem: Sprite too big/small

**Cause:** Wrong resize value

**Solution:**
```bash
# For characters (80x80)
-resize 80x80

# For tiles/items (64x64)
-resize 64x64

# For small details (48x48)
-resize 48x48
```

### Problem: Image distorted/stretched

**Cause:** Non-square original image

**Solution:**
```bash
# Crop to square first, then resize
magick input.jpeg \
  -gravity center \
  -crop 1:1 +repage \
  -resize 80x80 \
  output.xpm

# Or manually crop in Preview before converting
```

### Problem: Too many colors in XPM

**Cause:** Photos have many color variations

**Solution:**
```bash
# Reduce colors before conversion
magick input.jpeg \
  -colors 128 \
  -fuzz 20% -transparent white \
  -background "#FF00FF" -alpha remove -alpha off \
  -resize 80x80 \
  output.xpm
```

### Problem: Magenta showing in game

**Cause:** Code not using transparent rendering

**Solution:**
```c
// Make sure you're using:
draw_sprite_to_frame(&game->frame, &game->player, x, y);

// NOT:
draw_sprite_opaque(&game->frame, &game->player, x, y);
```

---

## 📁 File Organization

### Recommended Structure

```
so_long/
├── assets/
│   ├── sprites-louis/          # Louis source images & sprites
│   │   ├── louis-front.jpeg    # Original photo
│   │   ├── louis-front80.xpm   # Converted sprite
│   │   ├── louis-back80.xpm
│   │   ├── louis-left80.xpm
│   │   └── louis-right80.xpm
│   │
│   ├── sprites-ozzy/           # Ozzy sprites (bonus)
│   │   ├── ozzy-front.jpeg
│   │   └── ozzy-jump80.xpm
│   │
│   ├── cheese/                 # Collectible sprites
│   │   ├── cheese.jpeg
│   │   └── cheese.xpm
│   │
│   ├── exit/                   # Exit/goal sprites
│   │   ├── cat-furniture.jpeg
│   │   └── cat-furniture.xpm
│   │
│   └── temp/                   # Placeholder/test sprites
│       ├── wall.xpm
│       ├── floor.xpm
│       ├── cheese.xpm
│       ├── exit.xpm
│       └── player.xpm
```

---

## 🎨 Manual XPM Editing

### XPM File Structure

```c
/* XPM */
static char *sprite_name[] = {
/* columns rows colors chars-per-pixel */
"80 80 200 2 ",
/* Color definitions */
"   c #FF00FF",  // <-- Background (MAKE THIS MAGENTA!)
".  c #3E3B39",  // Dark color
"X  c #42413E",  // Another color
// ... more color definitions ...

/* Pixel data */
"                                        ",  // Row 1
"  ....XXXX....                          ",  // Row 2
// ... more rows ...
};
```

### How to Edit for Transparency

1. Open the `.xpm` file in VS Code
2. Find the **first color definition** (usually the background):
   ```c
   "   c #FFFFFF",  // or "   c None",
   ```
3. Change it to magenta:
   ```c
   "   c #FF00FF",
   ```
4. Save and test in game

### Tips

- The first color (`"  "` with spaces) is usually the background
- Don't change the pixel data (bottom part)
- Only change the color definition
- Use `#FF00FF` exactly (case-insensitive but consistent)

---

## 🚀 Quick Start Checklist

- [ ] Crop original photo in Preview (remove extra background)
- [ ] Export as JPEG
- [ ] Convert with ImageMagick (use transparency commands)
- [ ] Open XPM file and verify background is `#FF00FF`
- [ ] Update `texture_loader.c` to load the new sprite
- [ ] Recompile: `make`
- [ ] Test: `./so_long maps/test.ber`
- [ ] Verify transparency works in game

---

## 📚 Additional Resources

### ImageMagick Documentation
- Official: https://imagemagick.org/
- Examples: https://imagemagick.org/Usage/

### XPM Format
- Specification: https://en.wikipedia.org/wiki/X_PixMap
- MiniLibX: https://harm-smits.github.io/42docs/libs/minilibx

### Color Keying (Transparency)
- Also called "Chroma Key"
- Used in video/film green screens
- Same principle: select a color to make transparent

---

**Last Updated:** November 7, 2025  
**Status:** Transparency working perfectly! 🎉  
**Next:** Create more sprites with this workflow! 🐱🧀
