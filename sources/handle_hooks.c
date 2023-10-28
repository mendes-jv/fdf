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
static void	set_render_attributes(t_data *data);

void	handle_key_hooks(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
	set_render_attributes(data);
	manage_render(data);
}

void	handle_scroll_hook(double scroll_x, double scroll_y, t_data *data)
{
	manage_zoom(scroll_x > 0 || scroll_y > 0, scroll_x < 0 || scroll_y < 0,
				&data->camera->position->z);
	manage_render(data);
}

static void manage_axis_rotation(mlx_t *mlx, int *keys, double *axis)
{
	if(mlx_is_key_down(mlx, keys[0]))
		*axis += ROTATION_SPEED;
	else if(mlx_is_key_down(mlx, keys[1]))
		*axis -= ROTATION_SPEED;
	if (fabs(*axis) > PI_X_2)
		*axis -= *axis / fabs(*axis) * PI_X_2;
}

static void	manage_axis_translation(t_data *data, int *key_up, int *key_down, double *axis)
{
	if (mlx_is_key_down(data->mlx, key_down[0]) || mlx_is_key_down(data->mlx, key_down[1]))
		*axis -= sqrt(data->camera->position->z * 10);
	else if (mlx_is_key_down(data->mlx, key_up[0]) || mlx_is_key_down(data->mlx, key_up[1]))
		*axis += sqrt(data->camera->position->z * 10);
}

static void	manage_rotation(t_data *data)
{
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_Y, MLX_KEY_U}, &data->camera->rotation->x);
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_H, MLX_KEY_J}, &data->camera->rotation->y);
	manage_axis_rotation(data->mlx, (int [2]) {MLX_KEY_N, MLX_KEY_M}, &data->camera->rotation->z);
}

static void	manage_translation(t_data *data)
{
	manage_axis_translation(data, (int [2]){MLX_KEY_UP, MLX_KEY_W}, (int [2]){MLX_KEY_DOWN, MLX_KEY_S}, &data->camera->position->y);
	manage_axis_translation(data, (int [2]){MLX_KEY_LEFT, MLX_KEY_A}, (int [2]){MLX_KEY_RIGHT, MLX_KEY_D}, &data->camera->position->x);
}

static void manage_mirroring(t_data *data)
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

static void manage_centralization(t_data *data)
{
	double	zoom;

	zoom = 10;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || mlx_is_key_down(data->mlx, MLX_KEY_1)
		|| mlx_is_key_down(data->mlx, MLX_KEY_2) || mlx_is_key_down(data->mlx, MLX_KEY_3) ||
			mlx_is_key_down(data->mlx, MLX_KEY_4))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
			zoom = data->camera->position->z;
		*(data->camera->position) = (t_point) {((float) WIDTH + (float) MENU_WIDTH)/ 2, (float) HEIGHT / 2, zoom, 0};
		*(data->camera->rotation) = (t_point) {0, 0, 0, 0};
		*(data->camera->mirroring) = (t_point) {0, 0, 0, 0};
	}
}

static void	manage_zoom(int zoom_in, int zoom_out, double *zoom)
{
	if (zoom_in)
		(*zoom) += *zoom / 20;
	else if (zoom_out)
		(*zoom) -= *zoom / 20;
	*zoom = fmax(0, *zoom);
}

static void manage_color_mode(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Z)) //TODO: Check initialize when map is full white
		data->camera->color_mode = DEFAULT_COLOR_MODE;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_X))
		data->camera->color_mode = HENDRIX_COLOR_MODE;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->camera->color_mode = POLARITY_COLOR_SCHEME;
}

static void	manage_upscaling(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q) && data->camera->upscaling < 100)
		data->camera->upscaling++;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_E) && data->camera->upscaling > -100)
		data->camera->upscaling--;
}

static void	set_render_attributes(t_data *data)
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

static void	manage_render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->projection = apply_isometric;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_2))
		data->projection = apply_true_isometric;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_3))
		data->projection = NULL;
	render_map(data, apply_bresenham, data->projection);
	render_menu_background(data->image);
}
