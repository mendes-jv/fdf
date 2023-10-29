/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:21 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 01:45:24 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	read_map(t_list **list, int map_fd);
static void	split_line(t_list **list);
static void	split_values(t_list **list);
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
	map = ft_calloc(1, sizeof(t_map));
	read_map(&map->list, map_fd);
	split_line(&map->list);
	map->height = ft_lstsize(map->list);
	map->width = ft_arr_len(map->list->content);
	split_values(&map->list);
	parse_line(&map->list);
	return (map);
}

static void	read_map(t_list **list, int map_fd)
{
	char	*temp_line;
	size_t	length;

	temp_line = ft_get_next_line(map_fd);
	if (!temp_line)
		handle_error(INVALID_ARGUMENT_MESSAGE);
	while (temp_line)
	{
		length = ft_strlen(temp_line);
		if (ft_strchr(temp_line, '\n'))
			length--;
		ft_lstadd_back(list, ft_lstnew(ft_substr(temp_line, 0, length)));
		free(temp_line);
		temp_line = ft_get_next_line(map_fd);
	}
}

static void	split_line(t_list **list)
{
	t_list	*node;
	char	*old_content;

	node = *list;
	while (node)
	{
		old_content = node->content;
		node->content = ft_split(node->content, ' ');
		free(old_content);
		node = node->next;
	}
}

static void	split_values(t_list **list)
{
	t_list	*node;
	void	**old_content;

	node = *list;
	while (node)
	{
		old_content = node->content;
		node->content = ft_split_array(node->content, ',');
		ft_for_each(old_content, free);
		free(old_content);
		node = node->next;
	}
}

static void	parse_line(t_list **list)
{
	t_list		*node;
	t_values	*new_node;
	size_t		length;

	node = *list;
	while (node)
	{
		length = ft_arr_len(((char **)node->content));
		new_node = ft_calloc(length + 1, sizeof(t_values));
		while (length--)
			new_node[length] = (t_values){
				ft_atoi(((char ***)node->content)[length][0]),
				ft_atorgb(((char ***)node->content)[length][1])};
		ft_array_for_each(node->content, free, free);
		free(node->content);
		node->content = new_node;
		node = node->next;
	}
}
