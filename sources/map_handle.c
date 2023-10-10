/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:21 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/09 16:07:24 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_list *map_read(t_list *list, int map_fd);
static void	line_split(t_list *list);
static void	line_parse(t_list *list);

void	map_handle(char *map_str)
{
	int		map_fd;
	t_list	*map;

	map_fd = open(map_str, O_RDONLY);
	map = NULL;
	if (map_fd == -2)
		error_handle(OPEN_FAILURE_MESSAGE);
	map = map_read(map, map_fd);
	line_split(map);
	line_parse(map);
}

static t_list	*map_read(t_list *list, int map_fd) {
	t_list 	*node;
	char	*temp_line;

	temp_line = ft_get_next_line(map_fd);
	ft_printf ("\nGNL result:\n%s", temp_line);
	list = ft_lstnew(temp_line);
	while (temp_line) {
		temp_line = ft_get_next_line(map_fd);
		ft_printf ("%s", temp_line);
		if (!temp_line)
			break;
		ft_lstadd_back(&list,ft_lstnew(temp_line));
	}
	node = list;
	ft_printf("\n\nList content:\n");
	while (node)
	{
		ft_printf("%s", (char *)node->content);
		node = node->next;
	}
	return list;
}

static void	line_split(t_list *list)
{
	t_list	*node;
	char	*temp_content;

	node = list;
	ft_printf("\nSplitted content:\n");
	while (node)
	{
		temp_content = node->content;
		node->content = ft_split(node->content, ' ');
		free(temp_content);
		for (int i = 0; ((char **)node->content)[i]; i++)
			ft_printf("%3s", ((char **)node->content)[i]);
		node = node->next;
	}
}

static void	line_parse(t_list *list)
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
			ft_printf("%3i", ((int *)node->content)[j]);
		ft_printf("\n");
		node = node->next;
	}
}
