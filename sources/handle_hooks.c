/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:23:42 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:54:06 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	manage_render(t_data *data);
static void	manage_zoom(int zoom_in, int zoom_out, double *zoom);
static void	set_render_placement(t_data *data);

void	hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
	set_render_placement(data);
	manage_render(data);
}

void	scroll_hook(double scroll_x, double scroll_y, t_data *data)
{
	manage_zoom(scroll_x > 0 || scroll_y > 0, scroll_x < 0 || scroll_y < 0,
				&data->camera->position->z);
	manage_render(data);
}

static void manage_axis_rotation(mlx_t *mlx, int *keys, double *axis)
{
	if(mlx_is_key_down(mlx, keys[0]))
		*axis += TWO_DEGREE_IN_RADIAN;
	else if(mlx_is_key_down(mlx, keys[1]))
		*axis -= TWO_DEGREE_IN_RADIAN;
	if (fabs(*axis) > PI_X_2)
		*axis -= *axis / fabs(*axis) * PI_X_2;
}

static void	manage_axis_translation(mlx_t *mlx, int *key_up, int *key_down, double *axis)
{
	if (mlx_is_key_down(mlx, key_down[0]) || mlx_is_key_down(mlx, key_down[1]))
		*axis += 10;
	else if (mlx_is_key_down(mlx, key_up[0]) || mlx_is_key_down(mlx, key_up[1]))
		*axis -= 10;
}

static void	manage_rotation(t_data *data)
{
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_T, MLX_KEY_Y}, &data->camera->rotation->x);
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_G, MLX_KEY_H}, &data->camera->rotation->y);
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_B, MLX_KEY_N}, &data->camera->rotation->z);
}

static void	manage_translation(t_data *data)
{
	manage_axis_translation(data->mlx, (int [2]){MLX_KEY_UP, MLX_KEY_W}, (int [2]){MLX_KEY_DOWN, MLX_KEY_S}, &data->camera->position->y);
	manage_axis_translation(data->mlx, (int [2]){MLX_KEY_LEFT, MLX_KEY_A}, (int [2]){MLX_KEY_RIGHT, MLX_KEY_D}, &data->camera->position->x);
}

static void manage_mirroring(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		data->camera->mirroring->x = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->camera->mirroring->y = 1;
}

static void manage_centralization(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		*(data->camera->position) = (t_point) {(float) WIDTH / 2, (float) HEIGHT / 2, 10};
		*(data->camera->rotation) = (t_point) {0, 0, 0};
		*(data->camera->mirroring) = (t_point) {0, 0, 0};
	}
}

static void	manage_zoom(int zoom_in, int zoom_out, double *zoom)
{
	double zoom_speed;

	zoom_speed = 1;
	if (*zoom < 1)
		zoom_speed = 0.1;
	if (zoom_in)
		(*zoom) += zoom_speed;
	else if (zoom_out)
		(*zoom) -= zoom_speed;
	*zoom = fmax(0, *zoom);
}

static void	set_render_placement(t_data *data)
{
	manage_zoom(mlx_is_key_down(data->mlx, MLX_KEY_EQUAL),
				mlx_is_key_down(data->mlx, MLX_KEY_MINUS), &data->camera->position->z);
	manage_translation(data);
	manage_rotation(data);
	manage_mirroring(data);
	manage_centralization(data);
}

static void	manage_render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Z))
		data->projection = isometric;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_X))
		data->projection = NULL;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_V))
		;
	render_map(data, bresenham, data->projection);
}
