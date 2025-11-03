#include "so_long.h"

int	handle_keypress(int	keycode, void *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		exit(0);
	}
	return (0);
}

int	handle_close(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
	exit(0);
	return (0);
}

int main(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init(); // inicializa a MLX
    if (!mlx)
        return (1);

    win = mlx_new_window(mlx, 800, 600, "Hello, Louis!");
	if (!win)
		return (1);

	mlx_hook(win, 17, 0, handle_close, mlx);
	mlx_key_hook(win, handle_keypress, mlx);
	mlx_loop(mlx); // mantém a janela aberta

	return (0);
}
