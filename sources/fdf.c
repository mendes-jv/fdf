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

static void initialize_data(char *map_path, t_data **data);
static void free_data(t_data *data);

int	main(int argc, char **argv) {
	t_data	*data;

	data = NULL;
	if (!argv || argc != 2)
		handle_error(ARGUMENTS_ERROR_MESSAGE);
	initialize_data(argv[1], &data);
	handle_mlx(data);
	free_data(data);
	return (EXIT_SUCCESS);
}

static void initialize_data(char *map_path, t_data **data)
{
	t_list	*node;

	*data = ft_calloc(1 ,sizeof(t_data));
	(*data)->map = parse_map(map_path);
	node = (*data)->map->list;
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

int	ft_count_if(char **array, size_t (*f)(const char*))
{
	int	count;

	count = 0;
	while (*array)
		if (f(*(array++)))
			count++;
	return (count);
} //TODO: remove this function

void	ft_foreach_str(char **array, size_t length, void (*f)(char *))
{
	while (length--)
		f(*(array++));
} //TODO: remove this function
