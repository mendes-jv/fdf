/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:21 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:52:31 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void read_map(t_list **list, int map_fd);
static void	split_line(t_list **list);
static void split_values(t_list **list);
static void	parse_line(t_list **list);

t_map	*parse_map(char *map_str)
{
	int		map_fd;
	t_map	*map;

	if (!ft_strnstr(map_str, ".fdf", ft_strlen(map_str)))
		handle_error(INVALID_ARGUMENT_MESSAGE);
	map_fd = open(map_str, O_RDONLY);
	if (map_fd == -1)
		handle_error(OPEN_FAILURE_MESSAGE);
	map = ft_calloc(1,sizeof(t_map));
	read_map(&map->list, map_fd);
	split_line(&map->list);
	map->height = ft_lstsize(map->list);
	map->width = ft_arr_len(map->list->content);
	split_values(&map->list);
	parse_line(&map->list);
	return (map);
}

static void read_map(t_list **list, int map_fd)
{
	t_list 	*node;
	char	*temp_line;


	temp_line = ft_get_next_line(map_fd);
	if (!temp_line)
		handle_error(INVALID_ARGUMENT_MESSAGE);
	ft_printf ("\nGNL result:\n");
	while (temp_line) {
		ft_printf ("%s", temp_line);
		ft_lstadd_back(list,ft_lstnew(ft_substr(temp_line, 0, ft_strlen(temp_line) - 1)));
		free(temp_line);
		temp_line = ft_get_next_line(map_fd);
	}
	node = *list;
	ft_printf("\nList content:\n");
	while (node)
	{
		ft_printf("%s\n", (char *)node->content);
		node = node->next;
	}
}

static void	split_line(t_list **list)
{
	t_list	*node;
	char	*old_content;

	node = *list;
	ft_printf("\nSplitted content:\n");
	while (node)
	{
		old_content = node->content;
		node->content = ft_split(node->content, ' '); //TODO: macro for separators
		free(old_content);
		for (int i = 0; ((char **)node->content)[i]; i++)
			ft_printf("%-3s", ((char **)node->content)[i]);
		ft_printf("\n");
		node = node->next;
	}
}

static void split_values(t_list **list)
{
	t_list	*node;
	void	**old_content;

	node = *list;
	ft_printf("\nSplitted values:\n");
	while (node)
	{
		old_content = node->content;
		node->content = ft_split_array(node->content, ',');
		ft_for_each(old_content, free);
		free(old_content);
		for (int i = 0; ((char ***)node->content)[i]; i++)
			ft_printf("{%3s, %-7s}, ", ((char ***)node->content)[i][0], ((char ***)node->content)[i][1]);
		ft_printf("\n");
		node = node->next;
	}
}

static void	parse_line(t_list **list)
{
	t_list		*node;
	t_values	*new_node;
	size_t		length;
	size_t		width;

	node = *list;
	width = ft_arr_len((char **)node->content);
	ft_printf("\nPost struct transformation:\n");
	while (node)
	{
		length = ft_arr_len(((char **)node->content));
		new_node = ft_calloc(length + 1, sizeof(t_values)); //TODO: check this "+1" to change macro for all clear allocations
		while (length--)
			new_node[length] = (t_values){ft_atoi(((char ***)node->content)[length][0]),
										  ft_atorgb(((char ***)node->content)[length][1])};
		ft_array_for_each(node->content, free, free);
		free(node->content);
		node->content = new_node;
		for (size_t i = 0; i != width; ++i)
			ft_printf("{%3i, %10p}, ", ((t_values *)node->content)[i].altitude, ((t_values *)node->content)[i].color);
		ft_printf("\n");
		node = node->next;
	}
} //TODO: Improve this shit while(node) in all functions
