/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_camera_hooks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:48:40 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 01:37:27 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	manage_axis_rotation(mlx_t *mlx, int *keys, double *axis);
static void	manage_axis_translation(t_data *data, int *key_up, int *key_down,
				double *axis);

void	manage_rotation(t_data *data)
{
	manage_axis_rotation(data->mlx, (int [2]){MLX_KEY_Y, MLX_KEY_U},
		&data->camera->rotation->x);
	manage_axis_rotation(data->mlx, (int [2]){MLX_KEY_H, MLX_KEY_J},
		&data->camera->rotation->y);
	manage_axis_rotation(data->mlx, (int [2]){MLX_KEY_N, MLX_KEY_M},
		&data->camera->rotation->z);
}

static void	manage_axis_rotation(mlx_t *mlx, int *keys, double *axis)
{
	if (mlx_is_key_down(mlx, keys[0]))
		*axis += ROTATION_SPEED;
	else if (mlx_is_key_down(mlx, keys[1]))
		*axis -= ROTATION_SPEED;
	if (fabs(*axis) > PI_X_2)
		*axis -= *axis / fabs(*axis) * PI_X_2;
}

void	manage_translation(t_data *data)
{
	manage_axis_translation(data, (int [2]){MLX_KEY_UP, MLX_KEY_W},
		(int [2]){MLX_KEY_DOWN, MLX_KEY_S}, &data->camera->position->y);
	manage_axis_translation(data, (int [2]){MLX_KEY_LEFT, MLX_KEY_A},
		(int [2]){MLX_KEY_RIGHT, MLX_KEY_D}, &data->camera->position->x);
}

static void	manage_axis_translation(t_data *data, int *key_up, int *key_down,
								double *axis)
{
	if (mlx_is_key_down(data->mlx, key_down[0]) || mlx_is_key_down(data->mlx,
			key_down[1]))
		*axis -= sqrt(data->camera->position->z * 10);
	else if (mlx_is_key_down(data->mlx, key_up[0]) || mlx_is_key_down(data->mlx,
			key_up[1]))
		*axis += sqrt(data->camera->position->z * 10);
}

void	manage_mirroring(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		data->camera->mirroring->x = 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_T))
		data->camera->mirroring->x = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		data->camera->mirroring->y = 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_G))
		data->camera->mirroring->y = 0;
}
