/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:30:45 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:52:32 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	render_map(t_data *data, t_draw_f d_f, t_proj_f p_f)
{
	t_list 	*node;
	double	line;
	double	column;

	node = data->map->list;
	line = 0;
	while (line < (double)data->map->height)
	{
		column = 0;
		while (column < (double)data->map->width)
		{
			if (column < (double)data->map->width - 1)
				d_f(data, p_f, (t_point){column, line,((t_values *)
				node->content)[(int)column].altitude, 0},(t_point){column + 1, line, (
						(t_values *)node->content)[(int)column + 1].altitude, 0});
			if (line < (double)data->map->height - 1)
				d_f(data, p_f, (t_point){column, line,((t_values *)
				node->content)[(int)column].altitude, 0},(t_point){column, line + 1, (
						(t_values *)node->next->content)[(int)column].altitude, 0});
			column++;
		}
		line++;
		node = node->next;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

t_point	apply_true_isometric(t_point p)
{
	t_point	new_p;

	new_p.x = (p.x - p.z) / SQRT_2;
	new_p.y = (p.x + (2 * p.y) + p.z) / SQRT_6;
	new_p.z = p.z;
	return (new_p);
}

t_point	apply_isometric(t_point p)
{
	t_point	new_p;

	new_p.x = (p.x - p.y) * COS_0_8;
	new_p.y = (p.x + p.y) * SIN_0_8 - p.z;
	new_p.z = p.z;
	return (new_p);
}

t_point rotate_x(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x;
	new_p.y = p.y * cos(angle) - p.z * sin(angle);
	new_p.z = p.y * sin(angle) + p.z * cos(angle);
	return (new_p);
}

t_point rotate_y(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x * cos(angle) + p.z * sin(angle);
	new_p.y = p.y;
	new_p.z = -p.x * sin(angle) + p.z * cos(angle);
	return (new_p);
}

t_point	rotate_z(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x * cos(angle) - p.y * sin(angle);
	new_p.y = p.x * sin(angle) + p.y * cos(angle);
	new_p.z = p.z;
	return (new_p);
}

void	apply_bresenham(t_data *data, t_proj_f p_f, t_point p1, t_point p2)
{
	double x_ratio;
	double y_ratio;
	double bigger_axis;
	unsigned int color;

	if (p1.z > 0 || p2.z > 0)
		color = 0xFF0000FF;
	else if (p1.z < 0 || p2.z < 0)
		color = 0x0000FFFF;
	else
		color = 0xFFFFFFFF;
	// CENTERING
	p1.x -= (float) data->map->width / 2;
	p1.y -= (float) data->map->height / 2;
	p2.x -= (float) data->map->width / 2;
	p2.y -= (float) data->map->height / 2;
	// ZOOM
	p1.x *= data->camera->position->z;
	p1.y *= data->camera->position->z;
	p1.z *= data->camera->position->z  / 10;
	p2.x *= data->camera->position->z;
	p2.y *= data->camera->position->z;
	p2.z *= data->camera->position->z  / 10;
	// PROJECTION
	if (p_f)
	{
		p1 = p_f(p1);
		p2 = p_f(p2);
	}
	// MIRRORING
	if (data->camera->mirroring->x)
	{
		p1 = rotate_x(p1, M_PI);
		p2 = rotate_x(p2, M_PI);
	}
	if (data->camera->mirroring->y)
	{
		p1 = rotate_y(p1, M_PI);
		p2 = rotate_y(p2, M_PI);
	}
	// ROTATION
	p1 = rotate_x(p1, data->camera->rotation->x);
	p2 = rotate_x(p2, data->camera->rotation->x);
	p1 = rotate_y(p1, data->camera->rotation->y);
	p2 = rotate_y(p2, data->camera->rotation->y);
	p1 = rotate_z(p1, data->camera->rotation->z);
	p2 = rotate_z(p2, data->camera->rotation->z);
	// TRANSLATION
	p1.x += data->camera->position->x;
	p2.x += data->camera->position->x;
	p1.y += data->camera->position->y;
	p2.y += data->camera->position->y;
	x_ratio = p2.x - p1.x;
	y_ratio = p2.y - p1.y;
	bigger_axis = fmax(fabs(x_ratio), fabs(y_ratio));
	x_ratio /= bigger_axis;
	y_ratio /= bigger_axis;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		if ((int)p1.x < WIDTH && (int)p1.y < HEIGHT && (int)p1.x > MENU_WIDTH && (int)p1.y >= 0)
			mlx_put_pixel(data->image, (uint32_t)p1.x, (uint32_t)p1.y, color);
		p1.x += x_ratio;
		p1.y += y_ratio;
	}
}
