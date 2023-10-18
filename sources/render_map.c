/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:30:45 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/15 14:30:53 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//void	render_map(t_data *data)
//{
//	t_list	*node;
//	size_t	column;
//	size_t	edge;
//	size_t	ordinate;
//	size_t	abscissa;
//
//	node = data->map->list;
//	column = 0;
//	edge = EDGE_LENGTH;
//	ordinate = 0;
//	abscissa = 0;
//	while (node)
//	{
//		while (++column <= data->map->width)
//		{
//			if (node->next)
//			{
//				while (edge--)
//					mlx_put_pixel(data->image, abscissa, ordinate++, 0xFFFFFFFF);
//				edge = EDGE_LENGTH;
//				ordinate -= EDGE_LENGTH;
//			}
//			while (edge-- && column < data->map->width)
//				mlx_put_pixel(data->image, abscissa++, ordinate, 0xFFFFFFFF);
//			edge = EDGE_LENGTH;
//		}
//		abscissa = 0;
//		column = 0;
//		ordinate += EDGE_LENGTH;
//		node = node->next;
//	}
//}

void	render_map1(t_data *data, t_draw_f d_f, t_proj_f p_f)
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
				d_f(data->image, p_f, (t_point){column, line,((int *)
				node->content)[(int)column]},(t_point){column + 1, line, (
						(int *)node->content)[(int)column + 1]});
			if (line < (double)data->map->height - 1)
				d_f(data->image, p_f, (t_point){column, line,((int *)
				node->content)[(int)column]},(t_point){column, line + 1, (
						(int *)node->content)[(int)column]});
			column++;
		}
		line++;
		node = node->next;
	}
}

t_point	isometric1(t_point p)
{
	t_point	new_p;
	new_p.x = (p.x - p.z) / sqrt(2);
	new_p.y = (p.x + (2 * p.y) + p.z) / sqrt(6);
	new_p.z = 0;
	return (new_p);
}

void	bresenham1(mlx_image_t *image, t_proj_f p_f, t_point p1, t_point p2)
{
	double	x_ratio;
	double	y_ratio;
	double	bigger_axis;

//	p_f((t_point){0, 0, 0});
	p1 = p_f(p1);
	p2 = p_f(p2);
	p1.x *= EDGE_LENGTH;
	p1.y *= EDGE_LENGTH;
	p2.x *= EDGE_LENGTH;
	p2.y *= EDGE_LENGTH;
	x_ratio = fabs(p2.x - p1.x);
	y_ratio = fabs(p2.y - p1.y);
	bigger_axis = fmax(x_ratio, y_ratio);
	x_ratio /= bigger_axis;
	y_ratio /= bigger_axis;
	p1.x += 200;
	p1.y += 200;
	p2.x += 200;
	p2.y += 200;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		mlx_put_pixel(image, (uint32_t)p1.x, (uint32_t)p1.y, 0xFFFFFFFF);
		p1.x += x_ratio;
		p1.y += y_ratio;
	}
}
