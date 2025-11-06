# 🗺️ Map Validation - Complete Guide

## 📖 Overview

Map validation ensures that the `.ber` file contains a valid, playable game map. We check **7 critical rules** before allowing the game to start.

---

## ✅ The 7 Validation Rules

### 1. 🎯 **Correct File Extension (.ber)**

**What:** File must end with `.ber`  
**Why:** Standardization and file type identification

**Examples:**
- ✅ `maps/level1.ber`
- ✅ `test.ber`
- ❌ `map.txt`
- ❌ `level.berX`
- ❌ `game`

**Implementation:**
```c
int	has_ber_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)              // Must be at least 4 chars (.ber)
		return (0);
	// Compare last 4 characters with ".ber"
	if (ft_strncmp(filename + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}
```

---

### 2. 📐 **Rectangular Shape**

**What:** All lines must have the same length  
**Why:** Simplifies rendering and prevents index errors

**Valid:**
```
11111
10001
10001
11111
```
All lines: 5 characters ✅

**Invalid:**
```
11111
100001  ← 6 characters!
10001
11111
```
Different lengths ❌

**Implementation:**
```c
int	is_rectangular(char **map)
{
	int	len;
	int	i;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);  // First line length
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != (size_t)len)
			return (0);  // Different length found!
		i++;
	}
	return (1);
}
```

---

### 3. 🔤 **Valid Characters Only**

**What:** Only these 5 characters allowed:
- `0` - Empty space (floor)
- `1` - Wall
- `C` - Collectible
- `E` - Exit
- `P` - Player start position

**Why:** Prevents undefined behavior and ensures parseable map

**Valid:**
```
1111
1P0C1
10E1
1111
```

**Invalid:**
```
1111
1P0X1  ← 'X' is not allowed!
10E1
1111
```

**Implementation:**
```c
int	has_only_valid_chars(char **map)
{
	int		i, j;
	char	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			// Check if character is one of the 5 allowed
			if (c != '0' && c != '1' && c != 'C' && 
			    c != 'E' && c != 'P')
				return (0);  // Invalid character!
			j++;
		}
		i++;
	}
	return (1);
}
```

---

### 4. 🧱 **Closed by Walls**

**What:** All edges (borders) must be walls (`1`)  
**Why:** Prevents player from walking out of bounds

**Valid:**
```
11111  ← All 1's
1P0C1  ← First and last char are 1
10E01  ← First and last char are 1
11111  ← All 1's
```

**Invalid:**
```
10111  ← Top border has '0'!
1P0C1
10E01
11111
```

**Implementation:**
```c
int	has_closed_walls(char **map)
{
	int	i, j, width, height;

	// Calculate dimensions
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	
	// Check first and last row (all must be '1')
	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	
	// Check first and last column of each row
	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
```

---

### 5. 🎮 **Valid Element Counts**

**What:** Must have:
- Exactly **1** Player (P)
- Exactly **1** Exit (E)  
- At least **1** Collectible (C)

**Why:** Game needs one player, one goal, and something to collect

**Valid:**
```
1111
1P01
1C01  ← 1 P, 1 E, 2 C's ✅
10E1
1111
```

**Invalid - Duplicate Player:**
```
1111
1PP1  ← 2 players!
1C01
10E1
1111
```

**Invalid - No Collectibles:**
```
1111
1P01  ← No C!
1001
10E1
1111
```

**Implementation:**
```c
int	has_valid_counts(char **map)
{
	int	i, j, p_count, e_count, c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				p_count++;
			else if (map[i][j] == 'E')
				e_count++;
			else if (map[i][j] == 'C')
				c_count++;
			j++;
		}
		i++;
	}
	// Exactly 1 P, 1 E, and at least 1 C
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}
```

---

### 6. 🛤️ **Valid Path (Flood Fill)**

**What:** Player must be able to reach:
- All collectibles (C)
- The exit (E)

**Why:** Map must be solvable/winnable

**Valid:**
```
1111
1P01
1C01  ← Player can walk down, right, up to reach C and E
10E1
1111
```

**Invalid - Blocked Exit:**
```
111111
1P00C1
111111  ← Wall blocks path to E!
1000E1
111111
```

See `flood_fill_explained.md` for detailed explanation!

---

### 7. 📁 **File Readable**

**What:** File must exist and be readable  
**Why:** Can't load a map that doesn't exist!

**Implementation:**
```c
char	**read_map(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map");
		return (NULL);  // File doesn't exist or can't be read
	}
	// ... continue reading
}
```

---

## 🔄 Validation Order (Important!)

The order matters for good error messages:

```
1. Check argument count           → "invalid arguments"
2. Check .ber extension          → "missing .ber extension"
3. Read file                     → "invalid file"
4. Check rectangular             → "map is not rectangular"
5. Check valid characters        → "map has invalid characters"
6. Check closed walls            → "map is not closed by walls"
7. Check element counts          → "invalid number of elements"
8. Check valid path (flood fill) → "no valid path"
```

**Why this order?**
- Early checks are faster (don't waste time on obviously bad input)
- More specific errors help debugging
- Some checks depend on previous ones (e.g., can't check walls if not rectangular)

---

## 🎯 Main Validation Flow

```c
int	main(int argc, char **argv)
{
	char	**map;

	// Step 1: Check arguments
	if (argc != 2)
		return (handle_error(ERR_ARGS));
	
	// Step 2: Check extension
	if (!has_ber_extension(argv[1]))
		return (handle_error(ERR_NOBER));
	
	// Step 3: Read file
	map = read_map(argv[1]);
	if (!map)
		return (handle_error(ERR_FILE));
	
	// Step 4: Validate structure
	if (!is_rectangular(map))
		return (handle_error(ERR_NOT_RECTANG));
	
	// Step 5: Validate content
	if (!has_only_valid_chars(map))
		return (handle_error(ERR_CHARS_INVALID));
	
	// Step 6: Validate walls
	if (!has_closed_walls(map))
		return (handle_error(ERR_NOT_WALLS));
	
	// Step 7: Validate counts
	if (!has_valid_counts(map))
		return (handle_error(ERR_ELEM_INVALID));
	
	// Step 8: Validate path
	if (!has_valid_path(map))
		return (handle_error(ERR_NO_PATH));
	
	// All checks passed! Map is valid ✅
	// ... continue to game
}
```

---

## 📊 Quick Reference Table

| Rule | Check | Error Message |
|------|-------|---------------|
| Extension | Ends with `.ber` | `missing .ber extension` |
| Readable | File exists and opens | `invalid file` |
| Rectangle | All lines same length | `map is not rectangular` |
| Characters | Only 0,1,C,E,P | `map has invalid characters` |
| Walls | Borders all '1' | `map is not closed by walls` |
| Counts | 1P, 1E, ≥1C | `invalid number of elements` |
| Path | All C and E reachable | `no valid path` |

---

## 🧪 Testing Checklist

Create test maps for each error:

- [ ] `valid.ber` - Should pass all checks ✅
- [ ] `wrong_ext.txt` - Wrong extension ❌
- [ ] `not_rect.ber` - Different line lengths ❌
- [ ] `bad_char.ber` - Contains 'X' or other invalid char ❌
- [ ] `open_wall.ber` - Border has '0' ❌
- [ ] `no_player.ber` - Missing P ❌
- [ ] `two_exits.ber` - Has 2 E's ❌
- [ ] `no_collect.ber` - No C ❌
- [ ] `no_path.ber` - C or E unreachable ❌

---

## 💡 Common Mistakes to Avoid

### ❌ Not removing newlines
```c
// Wrong - includes '\n' in length check
len = ft_strlen(line);  // "1111\n" = 5

// Right - remove '\n' before checking
if (len > 0 && line[len - 1] == '\n')
	line[len - 1] = '\0';  // "1111" = 4
```

### ❌ Wrong validation order
```c
// Wrong - checking path before basic structure
if (!has_valid_path(map))      // Might crash on invalid map!
	return (0);
if (!is_rectangular(map))
	return (0);

// Right - check structure first
if (!is_rectangular(map))
	return (0);
if (!has_valid_path(map))      // Now safe
	return (0);
```

### ❌ Not freeing memory on errors
```c
// Wrong - leaks if error
map = read_map(file);
if (!is_valid(map))
	return (1);  // map not freed!

// Right - free before exiting
map = read_map(file);
if (!is_valid(map))
{
	ft_free_arr(map);
	return (1);
}
```

---

## 🎓 Understanding Check

Can you answer these?

1. Why check `.ber` extension before reading the file?
2. Why must the map be rectangular?
3. What happens if we have 0 collectibles?
4. Why check walls before checking path?
5. What does flood fill validate that wall checking doesn't?

<details>
<summary>Answers</summary>

1. **Fail fast** - No point reading a `.txt` file
2. Makes array indexing simple and prevents crashes
3. Game would be unwinnable (nothing to collect)
4. Can't validate path in a broken/open map
5. Flood fill checks **reachability**, walls only check **structure**

</details>

---

## 🚀 Next Steps

Once you understand all validations:
- ✅ FASE 1 Complete!
- → Move to FASE 2: Rendering
- → FASE 3: Player movement
- → FASE 4: Game logic

**Your map validator is the foundation of a solid game!** 🎮
