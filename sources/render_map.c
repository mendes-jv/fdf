/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:23:34 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/13 20:22:20 by jovicto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	render_map(t_data *data)
{
	t_list	*node;
	size_t 	column;
	size_t	edges_length;
	size_t	ordinate;
	size_t	abscissa;

	node = data->map->list;
	column = 0;
	edges_length = 100;
	ordinate = 0;
	abscissa = 0;
	while (node)
	{
		while (column <= data->map->width)
		{
			if (node->next)
			{
				while (edges_length--)
					mlx_put_pixel(data->image, abscissa, ordinate++, 0xFFFFFFFF);
				edges_length = 100;
				ordinate -= edges_length;
			}
			while (edges_length--)
				mlx_put_pixel(data->image, abscissa++, ordinate, 0xFFFFFFFF);
			edges_length = 100;
			column++;
		}
		if (node->next)
		{
			while (edges_length--)
				mlx_put_pixel(data->image, abscissa, ordinate++, 0xFFFFFFFF);
			edges_length = 100;
			ordinate -= edges_length;
		}
		abscissa = 0;
		column = 0;
		ordinate += edges_length;
		node = node->next;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
