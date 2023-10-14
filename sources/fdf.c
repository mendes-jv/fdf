/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:52:31 by jovicto2          #+#    #+#             */
/*   Updated: 2023/09/26 08:56:45 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void initialize_data(char *map_path);

int	main(int argc, char **argv) {

	if (!argv || argc != 2)
		handle_error(ARGUMENTS_ERROR_MESSAGE);
	initialize_data(argv[1]);
	return (EXIT_SUCCESS);
}

static void	initialize_data(char *map_path) {
	t_list	*node;
	t_data	*data;

	data = ft_calloc(1 ,sizeof(t_data));
	data->map = parse_map(map_path);
	node = data->map->list;
	ft_printf("\nMap content\n");
	ft_printf("width -> %i\n", data->map->width);
	ft_printf("height -> %i\n", data->map->height);
	ft_printf("map list content: \n");
	for (size_t i = 0; i != data->map->width - 1; ++i)
	{
		ft_printf("%-2i", ((int *)node->content)[i]);
		node = node->next;
	}
	ft_printf("\n");
	handle_mlx(data);
}

int	ft_count_if(char **array, int (*f)(char*))
{
	int	count;

	count = 0;
	while (*array)
		if (f(*(array++)))
			count++;
	return (count);
} //TODO: remove this function
