#include "../includes/fdf.h"

static void	ft_hook(void* param);

int main(void) {
	mlx_t *mlx;
	mlx_image_t *image;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "Static Image Noise Simulator", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx || !image || mlx_image_to_window(mlx, image, 0, 0) == -1) {
		if (mlx)
			mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void ft_hook(void* param) {
	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}