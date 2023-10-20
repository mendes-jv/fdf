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
	node = (*data)->map->list;
	(*data)->zoom = 25;
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
	free(data->map);
	free(data);
}
