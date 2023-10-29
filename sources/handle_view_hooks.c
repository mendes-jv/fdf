/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_view_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:23:42 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 01:42:49 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_render_attributes(t_data *data)
{
	manage_color_mode(data);
	manage_zoom(mlx_is_key_down(data->mlx, MLX_KEY_EQUAL),
		mlx_is_key_down(data->mlx, MLX_KEY_MINUS), &data->camera->position->z);
	manage_translation(data);
	manage_rotation(data);
	manage_mirroring(data);
	manage_upscaling(data);
	manage_centralization(data);
}

void	manage_zoom(int zoom_in, int zoom_out, double *zoom)
{
	if (zoom_in)
		(*zoom) += *zoom / 20;
	else if (zoom_out)
		(*zoom) -= *zoom / 20;
	*zoom = fmax(0, *zoom);
}

void	manage_color_mode(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Z))
		data->camera->color_mode = DEFAULT_COLOR_MODE;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_X))
		data->camera->color_mode = HENDRIX_COLOR_MODE;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->camera->color_mode = POLARITY_COLOR_SCHEME;
}

void	manage_upscaling(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q) && data->camera->upscaling < 100)
		data->camera->upscaling++;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_E)
		&& data->camera->upscaling > -100)
		data->camera->upscaling--;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_4))
		data->camera->upscaling = 0;
}

void	manage_centralization(t_data *data)
{
	double	zoom;

	zoom = (double)ft_ternary((WIDTH > HEIGHT), WIDTH / data->map->width,
			HEIGHT / data->map->height) / 3;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || mlx_is_key_down(data->mlx,
			MLX_KEY_1) || mlx_is_key_down(data->mlx, MLX_KEY_2)
		|| mlx_is_key_down(data->mlx, MLX_KEY_3))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
			zoom = data->camera->position->z;
		*(data->camera->position) = (t_point){((float)WIDTH + (float)MENU_WIDTH)
			/ 2, (float)HEIGHT / 2, zoom, 0};
		*(data->camera->rotation) = (t_point){0, 0, 0, 0};
		*(data->camera->mirroring) = (t_point){0, 0, 0, 0};
		data->camera->upscaling = 10;
	}
}
