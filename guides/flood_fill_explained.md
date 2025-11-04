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
	t_point	player;
	char	**visited;
	int		width, height;

	// Find where the player starts
	player = find_player(map);
	
	// Create a copy to mark visited cells
	visited = create_visited_map(width, height);
	
	// Start the flood from player position
	flood_fill(map, visited, player.x, player.y, width, height);
	
	// Check if all C and E were visited
	// If any C or E has visited[y][x] == 0, it's unreachable!
	
	free_visited(visited);
	return (all_collectibles_and_exit_were_reached);
}
```

### 2. **Core Algorithm: `flood_fill()`**

```c
static void	flood_fill(char **map, char **visited, int x, int y, int width, int height)
{
	// BASE CASES (stop conditions):
	
	// 1. Out of bounds?
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	
	// 2. Already visited this cell?
	if (visited[y][x])
		return;
	
	// 3. Hit a wall?
	if (map[y][x] == '1')
		return;
	
	// RECURSIVE STEP:
	
	// Mark current cell as visited
	visited[y][x] = 1;
	
	// Flood in all 4 directions
	flood_fill(map, visited, x + 1, y, width, height);  // →
	flood_fill(map, visited, x - 1, y, width, height);  // ←
	flood_fill(map, visited, x, y + 1, width, height);  // ↓
	flood_fill(map, visited, x, y - 1, width, height);  // ↑
}
```

---

## 🧠 Key Concepts

### Recursion
Each call explores one cell and spawns 4 more calls for adjacent cells. The recursion naturally stops when it hits walls or already-visited cells.

### Two Arrays
- `map[][]` - Original map (read-only, tells us where walls are)
- `visited[][]` - Tracking array (marks which cells we've reached)

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

- **Time:** O(width × height) - Each cell visited once
- **Space:** O(width × height) - Visited array + recursion stack

---

## ✅ Checklist for Understanding

- [ ] I understand what flood fill simulates (water spreading)
- [ ] I know why we need it (validate reachability)
- [ ] I understand the base cases (out of bounds, visited, wall)
- [ ] I understand the recursive step (mark + flood 4 directions)
- [ ] I can trace through an example manually
- [ ] I know when a map is invalid (unreachable C or E)

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
- **FASE 2:** Rendering the map (you already know which cells are valid!)
- **FASE 3:** Player movement (flood fill could help with move validation)
- **BONUS:** Pathfinding for enemy AI (similar concept!)

---

**Happy flooding!** 🌊🎮
