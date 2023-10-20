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

static void	zoom(int zoom_in, int zoom_out, t_data *data);
static void	manage_render(t_data *data);

void	hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
	zoom(mlx_is_key_down(data->mlx, MLX_KEY_EQUAL),
		mlx_is_key_down(data->mlx, MLX_KEY_MINUS), data);
	manage_render(data);
}

void	scroll_hook(double scroll_x, double scroll_y, t_data *data)
{
	zoom(scroll_x > 0 || scroll_y > 0, scroll_x < 0 || scroll_y < 0, data);
	manage_render(data);
}

static void	zoom(int zoom_in, int zoom_out, t_data *data)
{
	if (zoom_in)
		data->zoom++;
	else if (zoom_out)
		data->zoom--;
}

void	manage_render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	render_map(data, bresenham, isometric);
}
