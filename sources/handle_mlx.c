/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:33:44 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:52:30 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void handle_mlx(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
//	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->mlx
		|| !data->image
		|| mlx_image_to_window(data->mlx,data->image, 0, 0) == -1)
	{
		if (data->mlx)
			mlx_close_window(data->mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_scroll_hook(data->mlx, (mlx_scrollfunc) scroll_hook, data);
	mlx_loop_hook(data->mlx, (void (*)(void *)) hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
