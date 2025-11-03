#include "so_long.h"
# include "../libs/minilibix-linux/mlx.h"

int main(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init(); // inicializa a MLX
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 800, 600, "Hello, Louis! 🐱");
    if (!win)
        return (1);
    mlx_loop(mlx); // mantém a janela aberta
    mlx_destroy_window(mlx, win);
    return (0);
}