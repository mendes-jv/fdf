/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:30:45 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/28 23:56:24 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_point	get_point(double i, double j, t_values *content);

void	render_map(t_data *data, t_draw_f d_f, t_proj_f p_f)
{
	t_list	*node;
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
				d_f(data, p_f, get_point(column, line, node->content),
					get_point(column + 1, line, node->content));
			if (line < (double)data->map->height - 1)
				d_f(data, p_f, get_point(column, line, node->content),
					get_point(column, line + 1, node->next->content));
			column++;
		}
		line++;
		node = node->next;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

static t_point	get_point(double i, double j, t_values *content)
{
	return ((t_point){i, j,
		content[(int) i].altitude,
		content[(int) i].color});
}
