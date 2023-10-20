/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:30:45 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/19 22:55:39 by jovicto2         ###   ########.org.br   */
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
				d_f(data, p_f, (t_point){column, line,((int *)
				node->content)[(int)column]},(t_point){column + 1, line, (
						(int *)node->content)[(int)column + 1]});
			if (line < (double)data->map->height - 1)
				d_f(data, p_f, (t_point){column, line,((int *)
				node->content)[(int)column]},(t_point){column, line + 1, (
						(int *)node->next->content)[(int)column]});
			column++;
		}
		line++;
		node = node->next;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

t_point	true_isometric(t_point p)
{
	t_point	new_p;
	new_p.x = (p.x - p.z) / sqrt(2);
	new_p.y = (p.x + (2 * p.y) + p.z) / sqrt(6);
	new_p.z = p.z;
	return (new_p);
}

t_point	isometric(t_point p)
{
	t_point	new_p;
	new_p.x = (p.x - p.y) * cos(0.5235988);
	new_p.y = (p.x + p.y) * sin(0.5235988) - p.z;
	new_p.z = p.z;
	return (new_p);
}

void	bresenham(t_data *data, t_proj_f p_f, t_point p1, t_point p2)
{
	double			x_ratio;
	double			y_ratio;
	double			bigger_axis;
	unsigned int	color;

	if (p1.z > 0|| p2.z > 0)
		color = 0xFF0000FF;
	else if (p1.z < 0 || p2.z < 0)
		color = 0x0000FFFF;
	else
		color = 0xFFFFFFFF;
	p1.x *= data->zoom;
	p1.y *= data->zoom;
	p2.x *= data->zoom;
	p2.y *= data->zoom;
	p1 = p_f(p1);
	p2 = p_f(p2);
	x_ratio = p2.x - p1.x;
	y_ratio = p2.y - p1.y;
	bigger_axis = fmax(fabs(x_ratio), fabs(y_ratio));
	x_ratio /= bigger_axis;
	y_ratio /= bigger_axis;
	p1.x += 500;
	p2.x += 500;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		mlx_put_pixel(data->image, (uint32_t)p1.x, (uint32_t)p1.y, color);
		p1.x += x_ratio;
		p1.y += y_ratio;
	}
}
