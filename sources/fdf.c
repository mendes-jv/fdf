/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:52:31 by jovicto2          #+#    #+#             */
/*   Updated: 2023/09/26 08:56:45 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	hook(void *parameter);

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx || !image || mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		if (mlx)
			mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void	hook(void *parameter)
{
	if (mlx_is_key_down((mlx_t *)parameter, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t *)parameter);
}
