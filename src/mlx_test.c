#include "so_long.h"
#include <stdio.h>

int	handle_keypress(int	keycode, void *mlx)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == 65307 || keycode == 53)  // ESC on both Linux and macOS
	{
		mlx_destroy_display(mlx);
		free(mlx);
		exit(0);
	}
	return (0);
}

int	handle_close(void *mlx)
{
	printf("Window closed\n");
	mlx_destroy_display(mlx);
	free(mlx);
	exit(0);
	return (0);
}

int main(void)
{
    void    *mlx;
    void    *win;

	printf("Initializing MLX...\n");
    mlx = mlx_init();
    if (!mlx)
	{
		printf("Error: Failed to initialize MLX\n");
        return (1);
	}
	printf("MLX initialized successfully!\n");

	printf("Creating window...\n");
    win = mlx_new_window(mlx, 800, 600, "Hello, Louis!");
	if (!win)
	{
		printf("Error: Failed to create window\n");
		return (1);
	}
	printf("Window created successfully!\n");
	printf("Press ESC to close the window.\n");

	mlx_hook(win, 17, 0, handle_close, mlx);
	mlx_key_hook(win, handle_keypress, mlx);
	mlx_loop(mlx);

	return (0);
}
