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
				d_f(data, p_f, (t_point){column, line,
										 ((t_values *)node->content)[(int)column].altitude,
										 (((t_values *) node->content)[(int) column].color)},
					(t_point){column + 1, line, (
						(t_values *)node->content)[(int)column + 1].altitude, ((t_values *)node->content)[(int)column + 1].color});
			if (line < (double)data->map->height - 1) //TODO: apply ft_ternary to get to get triangled lines in bad maps
				d_f(data, p_f, (t_point){column, line,
										 ((t_values *)node->content)[(int)column].altitude, ((t_values *)node->content)[(int)column].color},
					(t_point){column, line + 1, (
						(t_values *)node->next->content)[(int)column].altitude, ((t_values *)node->next->content)[(int)column].color});
			column++;
		}
		line++;
		node = node->next;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
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

void	apply_bresenham(t_data *data, t_proj_f p_f, t_point p1, t_point p2)
{
	double	x_ratio;
	double	y_ratio;
	double	bigger_axis;
	long 	color;

	if (!p1.color || !p2.color)
		return ;
	// COLORING PIXELS
	color = (long) ft_ternary(fabs(p1.z) > fabs(p2.z), (long) p1.z, (long) p2.z);
	if (data->camera->color_mode == DEFAULT_COLOR_MODE)
		color = ft_ternary(color == (long)p1.z, p1.color, p2.color) * 0x100 + 0xFF;
	else if (data->camera->color_mode == HENDRIX_COLOR_MODE)
		color = ft_ternary(color, ft_ternary(color > 0 && color <= 3, 0xD16AFFFF,
											 ft_ternary(color > 3 && color <= 5, 0xBB44F0FF,
											   ft_ternary(color > 5 && color <= 15, 0x9614D0FF,
														  ft_ternary(color > 15 && color <= 25, 0x660094FF,
																	 ft_ternary(color > 25, 0x310047FF,
																				ft_ternary(color < 0 && color >= -3, 0xFFFB05FF,
																						   ft_ternary(color < -3 && color >= -5, 0xFFE505FF,
																									  ft_ternary(color < -5 && color >= -15, 0xFFC905FF,
																												 ft_ternary(color < -15 && color >= -25, 0xFFB805FF, 0xFFA505FF))))))))), 0xE8B382FF);
	else if (data->camera->color_mode == POLARITY_COLOR_SCHEME)
		color = ft_ternary(color, ft_ternary(color > 0, 0xB82230FF, 0x1C24D0FF), 0xFFFFFFFF);
	// CENTERING
	p1.x -= (float) (data->map->width - 1) / 2;
	p1.y -= (float) (data->map->height - 1) / 2;
	p2.x -= (float) (data->map->width - 1) / 2;
	p2.y -= (float) (data->map->height - 1) / 2;
	// ZOOMING
	p1.x *= data->camera->position->z;
	p1.y *= data->camera->position->z;
	p1.z *= data->camera->position->z / 5;
	p2.x *= data->camera->position->z;
	p2.y *= data->camera->position->z;
	p2.z *= data->camera->position->z / 5;
	// UPSCALING
	if (p1.z)
		p1.z += data->camera->upscaling;
	if (p2.z)
		p2.z += data->camera->upscaling;
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
	// ROTATING
	// TODO: change to pointer to don't use assignment
	p1 = rotate_x(p1, data->camera->rotation->x);
	p2 = rotate_x(p2, data->camera->rotation->x);
	p1 = rotate_y(p1, data->camera->rotation->y);
	p2 = rotate_y(p2, data->camera->rotation->y);
	p1 = rotate_z(p1, data->camera->rotation->z);
	p2 = rotate_z(p2, data->camera->rotation->z);
	// PROJECTING
	if (p_f)
	{
		p1 = p_f(p1);
		p2 = p_f(p2);
	}
	// TRANSLATING
	p1.x += data->camera->position->x;
	p2.x += data->camera->position->x;
	p1.y += data->camera->position->y;
	p2.y += data->camera->position->y;
	x_ratio = p2.x - p1.x;
	y_ratio = p2.y - p1.y;
	bigger_axis = fmax(fabs(x_ratio), fabs(y_ratio)); //TODO: See math calls
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
