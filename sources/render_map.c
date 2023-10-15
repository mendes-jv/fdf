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

void	render_map(t_data *data)
{
	t_list	*node;
	size_t 	column;
	size_t	edge;
	size_t	ordinate;
	size_t	abscissa;

	node = data->map->list;
	column = 0;
	edge = EDGE_LENGTH;
	ordinate = 0;
	abscissa = 0;
	while (node)
	{
		while (++column <= data->map->width)
		{
			if (node->next)
			{
				while (edge--)
					mlx_put_pixel(data->image, abscissa, ordinate++, 0xFFFFFFFF);
				edge = EDGE_LENGTH;
				ordinate -= EDGE_LENGTH;
			}
			while (edge-- && column < data->map->width)
				mlx_put_pixel(data->image, abscissa++, ordinate, 0xFFFFFFFF);
			edge = EDGE_LENGTH;
		}
		abscissa = 0;
		column = 0;
		ordinate += EDGE_LENGTH;
		node = node->next;
	}
}
