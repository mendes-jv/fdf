/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:21 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/11 22:32:01 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void read_map(t_list **list, int map_fd);
static void	split_line(t_list **list);
static void	parse_line(t_list *list);

t_map	*parse_map(char *map_str)
{
	int		map_fd;
	t_map	*map;
	t_list	*node;

	map_fd = open(map_str, O_RDONLY);
	if (map_fd == -1)
		handle_error(OPEN_FAILURE_MESSAGE);
	map = ft_calloc(1,sizeof(t_map));
	read_map(&map->list, map_fd);
	split_line(&map->list);
	map->height = ft_lstsize(map->list);
	map->width = ft_count_if(map->list->content, (int (*)(char *)) ft_strlen);
	parse_line(map->list);
	node = map->list;
	for (size_t i = 0; i != map->width - 1; ++i)
	{
		ft_printf("%-2i", ((int *)node->content)[i]);
		node = node->next;
	}
	return (map);
}

static void read_map(t_list **list, int map_fd) {
	t_list 	*node;
	char	*temp_line;

	temp_line = ft_get_next_line(map_fd);
	ft_printf ("\nGNL result:\n%s", temp_line);
	*list = ft_lstnew(temp_line);
	while (temp_line) {
		temp_line = ft_get_next_line(map_fd);
		ft_printf ("%s", temp_line);
		if (!temp_line)
			break;
		ft_lstadd_back(list,ft_lstnew(temp_line));
	}
	node = *list;
	ft_printf("\n\nList content:\n");
	while (node)
	{
		ft_printf("%s", (char *)node->content);
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
		node->content = ft_split(node->content, ' ');
		free(old_content);
		for (int i = 0; ((char **)node->content)[i]; i++)
			ft_printf("%-2s", ((char **)node->content)[i]);
		node = node->next;
	}
}

static void	parse_line(t_list *list)
{
	t_list	*node;
	int 	*new_node;
	int		index;
	int		i;

	node = list;
	index = 0;
	ft_printf("\nPost itoa content:\n");
	while (node)
	{
		while (((char **)node->content)[index])
			index++;
		new_node = ft_calloc(index, sizeof(int));
		i = index;
		while (index--)
			new_node[index] = ft_atoi(((char **)node->content)[index]);
		free(node->content);
		node->content = new_node;
		for (int j = 0; i != j; ++j)
			ft_printf("%-2i", ((int *)node->content)[j]);
		ft_printf("\n");
		node = node->next;
	}
	ft_printf("\n");
}