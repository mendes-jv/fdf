#include "../includes/fdf.h"

int main(void) {
	mlx_t *mlx;
	mlx_image_t *image;

	mlx = mlx_init(WIDTH, HEIGHT, "Static Image Noise Simulator", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx || !image || mlx_image_to_window(mlx, image, 0, 0) == -1) {
		if (mlx)
			mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}