/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:55:36 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:52:28 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void initialize_data(char *map_path, t_data **data)
{
	t_list	*node;

	*data = ft_calloc(1 ,sizeof(t_data));
	(*data)->map = parse_map(map_path);
	(*data)->camera = ft_calloc(1, sizeof(t_camera));
	(*data)->camera->position = ft_calloc(1, sizeof(t_point));
	(*data)->camera->rotation = ft_calloc(1, sizeof(t_point));
	node = (*data)->map->list;
	(*data)->camera->position->x = 500;
	(*data)->camera->position->y = 500;
	(*data)->camera->position->z = 0;
	(*data)->camera->rotation->x = 0;
	(*data)->camera->rotation->y = 0;
	(*data)->camera->rotation->z = 0;
	ft_printf("\nParsed map content:\n");
	while (node)
	{
		for (size_t i = 0; i != (*data)->map->width; ++i)
			ft_printf("%-3i", ((int *) node->content)[i]);
		node = node->next;
		ft_printf("\n");
	}
	ft_printf("width -> %i\n", (*data)->map->width);
	ft_printf("height -> %i\n", (*data)->map->height);
}

void free_data(t_data *data)
{
	ft_lstclear(&data->map->list, free);
	free(data->camera->rotation);
	free(data->camera->position);
	free(data->camera);
	free(data->map);
	free(data);
}
