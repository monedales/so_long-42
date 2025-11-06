# 🎨 Asset Conversion Guide - Louis vs Ozzy

## 📸 Your Current Assets

**Location:** `assets/so_long-sprites/`

**Files:**
- `louis-frente-crop.jpeg` - Louis front view
- `louis-inteiro.jpeg` - Louis full body
- `louis-pos.jpeg` - Louis pose 1
- `louis-pos2.jpeg` - Louis pose 2
- `ozzy-frente.jpeg` - Ozzy front view
- `ozzy-pos.jpeg` - Ozzy pose
- `ozzy-pulando.jpeg` - Ozzy jumping

**Format:** JPEG (photos)
**Need:** XPM or PNG sprites for top-down game

---

## 🎯 Game Design - Side-View Edition!

### ✅ You're Right! Subject Allows Side-View!

The subject says:
> "Você deve usar uma visão 2D (de cima para baixo **ou de perfil**)"

**So your Mario-style idea is PERFECT!** 🎮

**Your Game (Side-view platformer):**
```
🧱🧱🧱🧱🧱🧱🧱
        🧀
🧱  🐱  🧱  🧱
    🧱🧱🧱
🧀         🛋️
🧱🧱🧱🧱🧱🧱🧱
```

### 🏠 Your Theme - Side View:

**Setting:** Side view of your apartment

| Element | Your Theme | Game Element |
|---------|------------|--------------|
| Floor (0) | Empty space / Air | Background (walkable) |
| Wall (1) | Platforms / Furniture | Platforms to walk on |
| Player (P) | Louis the cat (side view) | Walking left/right |
| Enemy (Bonus) | Ozzy the cat | Chasing Louis |
| Collectible (C) | Cheese 🧀 | Floating items to collect |
| Exit (E) | Cat furniture (bed/tree) | Goal to reach |

**Story:** Louis needs to navigate through the apartment (side-view), jumping between furniture pieces to collect all the cheese and reach his favorite cat furniture! Meanwhile, Ozzy might chase him! 🐱🧀

**Movement:**
- ⬅️➡️ Walk left/right (A/D or arrows)
- ⬆️⬇️ Optional: Jump/crouch OR just move up/down platforms
- **Note:** For simplicity, so_long usually doesn't have gravity/jumping - just 4-direction grid movement

---

## 🔧 Conversion Process

### Step 1: Choose Which Photos to Use

**For Louis (Player) - Side View:**
- **Best choice:** `louis-pos.jpeg` or `louis-pos2.jpeg` (side profile!)
- These are PERFECT for side-view platformer
- You can flip the image for left/right facing

**For Ozzy (Enemy - Bonus only):**
- **Best choice:** `ozzy-pos.jpeg` (side view)
- Or `ozzy-pulando.jpeg` if you want jumping animation

**Why these work:** Side-view photos are ideal for side-scrolling games!

### Step 2: Edit Photos into Sprites

You need to convert photos → small square sprites (64x64 pixels)

**Tools you can use:**

#### Option A: Online Tools (Easiest)
1. **Pixlr.com** (free, no signup)
   - Upload photo
   - Crop to square
   - Resize to 64x64
   - Remove background (if possible)
   - Export as PNG

2. **Remove.bg** (free, removes background)
   - Upload cat photo
   - Get PNG with transparent background
   - Then resize to 64x64

#### Option B: macOS Built-in
1. **Preview app:**
   - Open image
   - Tools → Adjust Size → 64x64
   - Tools → Select → crop to square
   - Export as PNG

#### Option C: Professional (if you have it)
- **Photoshop**
- **GIMP** (free)
- **Affinity Photo**

### Step 3: Convert PNG to XPM

Once you have PNG sprites, convert to XPM for MLX:

**Method 1: Online converter**
```
1. Search "PNG to XPM converter online"
2. Upload your 64x64 PNG
3. Download XPM file
```

**Method 2: ImageMagick (command line)**
```bash
# Install ImageMagick
brew install imagemagick

# Convert
convert louis.png louis.xpm
convert ozzy.png ozzy.xpm
convert cheese.png cheese.xpm
```

**Method 3: Manual XPM creation**
- XPM is just text, you can create it manually
- See example below

---

## 🎨 What You Need to Create

### Required Sprites (5 minimum) - SIDE VIEW:

1. **louis.xpm** - Louis side profile 64x64 (from `louis-pos.jpeg`)
2. **background.xpm** - White wall/background 64x64
3. **platform.xpm** - Furniture platforms 64x64
4. **cheese.xpm** - Cheese piece 🧀 64x64
5. **cat_furniture.xpm** - Cat bed/tree as exit 64x64

### Optional (for polish):
6. **ozzy.xpm** - Ozzy side profile (from `ozzy-pos.jpeg`)
7. **louis_left.xpm** - Louis facing left (flipped version)
8. **louis_right.xpm** - Louis facing right

**Note:** In side-view games, the "floor" (0) is typically sky/background, and "walls" (1) are the platforms!

---

## 🧀 Finding/Creating Missing Assets

Since you only have cat photos, you need:

### Cheese Sprite:
**Option 1:** Download free cheese emoji/icon
- Search: "cheese icon PNG transparent"
- Resize to 64x64
- Convert to XPM

**Option 2:** Create simple cheese
- Yellow triangle with holes
- Very simple in any drawing app

**Option 3:** Use emoji
```bash
# On macOS, convert emoji to image (requires extra tools)
# Or just screenshot an emoji and crop
```

### Cat Furniture (Exit):
**Option 1:** Photo of your actual cat furniture!
- Take photo
- Crop and resize to 64x64
- Convert to XPM

**Option 2:** Download cat tree icon
- Search: "cat tree icon PNG"
- Or cat bed icon

### Wall/Furniture:
**Option 1:** Photo of your wall
- Take a photo
- Make it tile-able 64x64
- Convert to XPM

**Option 2:** Solid color
- Simple white or beige square
- Add border for definition

### Floor:
- White or light gray square
- Maybe subtle texture
- Should look different from walls

---

## 📐 Sprite Requirements

### Size:
- **All sprites MUST be same size** (64x64 recommended)
- Square aspect ratio (64x64, 32x32, 128x128)

### Format:
- **XPM** (best for MLX) or PNG

### Transparency:
- Background should be transparent (or same as floor color)
- XPM supports transparency with `"None"` color

### Orientation:
- Top-down view (looking down at cats)
- If using front view, it still works (cat facing you while walking around)

---

## 🛠️ Quick Action Plan

### Option 1: Quick & Functional (30 minutes)
```
1. Use one Louis photo as-is (crop/resize to 64x64)
2. Find cheese emoji → resize → XPM
3. Photo of your cat furniture → resize → XPM  
4. White square for floor
5. Gray square for walls
✅ Functional game with your theme!
```

### Option 2: Polished (2-3 hours)
```
1. Edit Louis photo: remove background, resize, clean up
2. Edit Ozzy photo (for bonus)
3. Find/create cute cheese sprite
4. Photo of real cat furniture with background removed
5. Textured floor (photo of your floor)
6. Textured walls (photo of furniture)
✅ Professional looking game!
```

### Option 3: Placeholder First (15 minutes)
```
1. Colored squares for everything
2. Code the entire game
3. Replace sprites later with real photos
✅ Learn rendering without art blocking you!
```

---

## 💡 My Recommendation for You

Based on your photos and side-view game design:

### Phase 1 (Today): Get it working
1. **Louis**: Use `louis-pos.jpeg` or `louis-pos2.jpeg` → resize 64x64 PNG → convert XPM
2. **Background**: Light blue or white square (sky/wall background)
3. **Platform**: Dark brown/gray square (furniture platforms)
4. **Cheese**: Find cheese emoji PNG → resize → convert XPM
5. **Exit**: Use colored square for now OR quick photo of your cat furniture

### Phase 2 (After game works): Polish
1. Remove backgrounds from cat photos (transparent background)
2. Take nice photo of your cat furniture
3. Flip Louis sprite for left/right facing animations
4. Add Ozzy using `ozzy-pos.jpeg` (enemy bonus)
5. Maybe add `ozzy-pulando.jpeg` for jumping/chasing animation

---

## 🎯 File Organization Target

```
assets/
├── sprites/
│   ├── louis.xpm          ← From louis-pos.jpeg (side view!)
│   ├── background.xpm     ← Light color (sky/wall)
│   ├── platform.xpm       ← Dark color (furniture)
│   ├── cheese.xpm         ← Cheese icon/emoji
│   ├── cat_furniture.xpm  ← Photo of your furniture
│   └── ozzy.xpm          ← (Bonus) From ozzy-pos.jpeg
└── so_long-sprites/       ← Your original photos (keep!)
    ├── louis-pos.jpeg     ← PERFECT for side-view!
    ├── louis-pos2.jpeg    ← Alternative pose
    ├── ozzy-pos.jpeg      ← PERFECT for enemy!
    └── ozzy-pulando.jpeg  ← Jumping animation!
```

---

## 🧪 Test Your Sprites

Once created, test with this code:

```c
// Test loading
void	*mlx = mlx_init();
void	*img = mlx_xpm_file_to_image(mlx, "assets/sprites/louis.xpm", &w, &h);
if (!img)
	printf("Failed to load!\n");
else
	printf("Success! Size: %dx%d\n", w, h);
```

---

## ⚠️ Common Issues

### JPEG → XPM Problems:
**Problem:** MLX doesn't support JPEG directly  
**Solution:** Convert JPEG → PNG → XPM

### Background Not Transparent:
**Problem:** White background around cat  
**Solution:** Use remove.bg or manually remove in photo editor

### Wrong Size:
**Problem:** Photos are different sizes  
**Solution:** Resize ALL to same size (64x64)

### Quality Loss:
**Problem:** Photo looks bad at 64x64  
**Solution:** That's normal! Small sprites are stylized, not photo-realistic

---

## 🚀 Next Steps

1. **Decide:** Quick placeholders or edit photos now?
2. **Create:** The 5 required sprites
3. **Test:** Load one sprite in MLX
4. **Continue:** FASE 2 rendering implementation

**Want me to:**
- A) Help you create placeholder sprites right now?
- B) Write a bash script to batch convert your JPEGs?
- C) Create simple XPM files with solid colors to start?

What would help you most? 🎨🐱
