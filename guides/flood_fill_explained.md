# 🌊 Flood Fill Algorithm - Path Validation

## 📖 What is Flood Fill?

Flood fill is a classic algorithm used to determine **connected regions** in a grid. Think of it like pouring water on a surface - the water spreads to all connected areas until it hits barriers (walls).

In **so_long**, we use flood fill to verify that the player can reach:
- ✅ All collectibles (C)
- ✅ The exit (E)

If any collectible or the exit is unreachable, the map is invalid.

---

## 🎯 Why Do We Need It?

Consider this map:

```
1111111
1P0C001  ← Player (P) and Collectible (C) on left
1111101  ← Wall blocks the path!
100E001  ← Exit (E) is on the right, unreachable!
1111111
```

**Without flood fill:** We'd check walls, counts, etc. - everything looks OK ❌  
**With flood fill:** We discover the exit is unreachable ✅

---

## 🔧 How It Works

### Step-by-step visualization:

**Initial map:**
```
1111
1P01
1C01
11E1
1111
```

**Step 1:** Start at Player (P)
```
1111
1X01  ← Mark P as visited (X)
1C01
11E1
1111
```

**Step 2:** Flood to adjacent cells (up, down, left, right)
```
1111
1XX1  ← Flood right (0 becomes X)
1C01
11E1
1111
```

**Step 3:** Continue flooding recursively
```
1111
1XX1
1XX1  ← Flood down to C
11E1
1111
```

**Step 4:** Keep going...
```
1111
1XX1
1XX1
11X1  ← Flood to E
1111
```

**Result:** All cells marked with X were reachable!  
- C was reached ✅  
- E was reached ✅  
- Map is valid! ✅

---

## 💻 Implementation Breakdown

### 1. **Main Function: `has_valid_path()`**

```c
int	has_valid_path(char **map)
{
	t_point			player;
	char			**visited;
	t_flood_params	params;
	int				result;

	// 1. Find where the player starts
	player = find_player(map);
	if (player.x == -1 || player.y == -1)
		return (0);
	
	// 2. Calculate map dimensions
	params.height = 0;
	while (map[params.height])
		params.height++;
	params.width = ft_strlen(map[0]);
	
	// 3. Create a copy to mark visited cells
	visited = create_visited_map(params.width, params.height);
	if (!visited)
		return (0);
	
	// 4. Start the flood from player position
	params.x = player.x;
	params.y = player.y;
	flood_fill_helper(map, visited, params);
	
	// 5. Check if all C and E were visited
	result = check_accessible(map, visited, params.height);
	
	// 6. Free memory and return result
	free_visited(visited);
	return (result);
}
```

### 2. **Helper Functions**

#### `find_player()` - Locates the starting position
```c
t_point	find_player(char **map)
{
	t_point	pos;
	int		i;
	int		j;

	pos.x = -1;
	pos.y = -1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);  // Returns (-1, -1) if not found
}
```

#### `create_visited_map()` - Allocates tracking array
```c
char	**create_visited_map(int width, int height)
{
	char	**visited;
	int		i;

	// Allocate array of row pointers
	visited = ft_calloc(height + 1, sizeof(char *));
	if (!visited)
		return (NULL);
	
	// Allocate each row (all initialized to 0)
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width + 1, sizeof(char));
		if (!visited[i])
		{
			free_visited_partial(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}
```

#### `check_accessible()` - Validates reachability
```c
int	check_accessible(char **map, char **visited, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			// If found C or E that wasn't visited, path is invalid
			if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);  // All collectibles and exit are reachable!
}
```

### 3. **Core Algorithm: `flood_fill_helper()`**

```c
void	flood_fill_helper(char **map, char **visited, t_flood_params p)
{
	// BASE CASES (stop conditions):
	
	// 1. Out of bounds?
	if (p.x < 0 || p.x >= p.width || p.y < 0 || p.y >= p.height)
		return;
	
	// 2. Already visited this cell OR hit a wall?
	if (visited[p.y][p.x] || map[p.y][p.x] == '1')
		return;
	
	// RECURSIVE STEP:
	
	// Mark current cell as visited
	visited[p.y][p.x] = 1;
	
	// Flood in all 4 directions (modifying params for each direction)
	p.x++;
	flood_fill_helper(map, visited, p);  // → Right
	p.x -= 2;
	flood_fill_helper(map, visited, p);  // ← Left
	p.x++;
	p.y++;
	flood_fill_helper(map, visited, p);  // ↓ Down
	p.y -= 2;
	flood_fill_helper(map, visited, p);  // ↑ Up
}
```

### 4. **Data Structure: `t_flood_params`**

```c
typedef struct s_flood_params
{
	int	x;       // Current X position
	int	y;       // Current Y position
	int	width;   // Map width (for bounds checking)
	int	height;  // Map height (for bounds checking)
}	t_flood_params;
```

This structure packages all necessary information for the recursive flood fill, making the function signature cleaner and parameter passing more efficient.

---

## 🧠 Key Concepts

### Recursion
Each call explores one cell and spawns 4 more calls for adjacent cells. The recursion naturally stops when it hits walls or already-visited cells.

### t_flood_params Structure
Instead of passing many parameters individually, we use a structure (`t_flood_params`) to package:
- Current position (x, y)
- Map dimensions (width, height)

This makes the code cleaner and avoids passing too many arguments to the recursive function.

### Two Arrays
- `map[][]` - Original map (read-only, tells us where walls are)
- `visited[][]` - Tracking array (marks which cells we've reached)

We keep them separate because:
1. We don't want to modify the original map
2. The visited array is temporary and gets freed after validation
3. We can mark visited cells with `1` while the map uses different characters

### Memory Management
The implementation includes careful memory management:
- `create_visited_map()` uses `ft_calloc()` to initialize all cells to 0
- `free_visited_partial()` handles partial cleanup if allocation fails
- `free_visited()` frees the entire visited array after validation

### Why It Works
If you can walk from P to a cell in the game, the flood fill will reach it. If flood fill can't reach a cell, neither can the player!

---

## 🎓 Example Walkthrough

### Valid Map:
```
1111
1PE1
1C01
1111
```

**Flood fill from P:**
1. Start at P (1,1)
2. Flood right to E (2,1) ✅
3. Can't reach C directly from P
4. Go down to (1,2) 
5. Flood right to C (2,2) ✅

**All elements reached!** ✅

---

### Invalid Map:
```
1111
1PE1
1111  ← Wall blocks downward path!
10C1
1111
```

**Flood fill from P:**
1. Start at P (1,1)
2. Flood right to E (2,1) ✅
3. Try to go down - blocked by wall! ❌
4. No other paths available

**C at (2,3) is unreachable!** ❌  
**Map is invalid!**

---

## 🔍 Complexity

- **Time:** O(width × height) - Each cell visited at most once
- **Space:** O(width × height) - For the visited array + O(width × height) for recursion stack in worst case
  
### Why is it efficient?
- Each cell is marked as visited when first reached
- Subsequent attempts to visit the same cell return immediately
- Walls stop the recursion from spreading further
- Maximum recursion depth is limited by map size

---

## ✅ Checklist for Understanding

- [ ] I understand what flood fill simulates (water spreading)
- [ ] I know why we need it (validate reachability)
- [ ] I understand the base cases (out of bounds, visited, wall)
- [ ] I understand the recursive step (mark + flood 4 directions)
- [ ] I can trace through an example manually
- [ ] I know when a map is invalid (unreachable C or E)
- [ ] I understand the role of `t_flood_params` structure
- [ ] I understand how `check_accessible()` validates the result
- [ ] I know why we need separate `map[][]` and `visited[][]` arrays

---

## 🎮 Try It Yourself!

Draw these maps on paper and manually trace the flood fill:

**Exercise 1:**
```
11111
1P0C1
11111
10E01
11111
```
Is this valid? Can you reach E? Can you reach C?

**Exercise 2:**
```
111111
1P00C1
101101
10E001
111111
```
Is this valid? Trace the flood from P!

<details>
<summary>Solutions</summary>

**Exercise 1:** ❌ Invalid - E is in a separate room, unreachable!

**Exercise 2:** ✅ Valid - All cells are reachable by going around the walls!

</details>

---

## 🚀 Next Steps

Once you understand flood fill, you're ready for:
- **Game Rendering:** Use the validated map to draw the game world
- **Player Movement:** Implement collision detection (similar boundary checks)
- **Animation System:** Build on the working game loop
- **BONUS:** Pathfinding for enemy AI (similar flood fill concept!)

---

## 📚 Related Files in the Project

- **Implementation:** [pathfinding.c](../src/pathfinding.c) - Complete flood fill implementation
- **Header:** [so_long.h](../include/so_long.h) - Structure definitions (`t_flood_params`, `t_point`)
- **Validation:** [map_validator.c](../src/map_validator.c) - Calls `has_valid_path()` as part of validation
- **Test Maps:** [maps/](../maps/) - Try `no_path.ber` to see flood fill catch invalid maps!

---

**Happy flooding!** 🌊🎮
