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

static void	hook(void *parameter);
static void	handle_mlx(void);
static void	handle_map(char *);
static void	line_splitter(t_list *lst);
static void	line_parser(t_list *lst);

int	main(int argc, char **argv) {
	if (!argv || argc != 2)
	{
		perror(ARGUMENTS_ERROR_MESSAGE);
		return (EXIT_FAILURE);
	}
	handle_map(argv[1]);
	handle_mlx();
	return (EXIT_SUCCESS);
}

void	hook(void *parameter)
{
	if (mlx_is_key_down((mlx_t *)parameter, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t *)parameter);
}

void handle_mlx(void)
{
	mlx_t *mlx;
	mlx_image_t *image;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx || !image || mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		if (mlx)
			mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	handle_map(char *map_str)
{
	int		map_fd;
	char	*temp_line;
	t_list 	*map_lines;

	map_fd = open(map_str, O_RDONLY);
	if (map_fd == -1)
	{
		perror(OPEN_FAILURE_MESSAGE);
		exit(EXIT_FAILURE);
	}
	temp_line = ft_get_next_line(map_fd);
	ft_printf ("%s", temp_line);
	map_lines = ft_lstnew(temp_line);
	while (temp_line) {
		temp_line = ft_get_next_line(map_fd);
		ft_printf ("%s", temp_line);
		if (!temp_line)
			break;
		ft_lstadd_back(&map_lines,ft_lstnew(temp_line));
	}
	t_list *temp_list = map_lines;
	ft_printf("\n");
	while (temp_list)
	{
		ft_printf("%s", (char *)temp_list->content);
		temp_list = temp_list->next;
	}
	line_splitter(map_lines);
	line_parser(map_lines);
}

void	line_splitter(t_list *lst)
{
	t_list	*node;
	char	*temp_content;

	node = lst;
	ft_printf("\n");
	while (node)
	{
		temp_content = node->content;
		node->content = ft_split(node->content, ' ');
		free(temp_content);
		for (int i = 0; ((char **)node->content)[i]; i++)
			ft_printf("%4s", ((char **)node->content)[i]);
		node = node->next;
	}
}

void	line_parser(t_list *lst)
{
	t_list	*node;
	int 	*new_node;
	int		index;
	int		i;


	node = lst;
	index = 0;
	while (node)
	{
		while (((char **)node->content)[index])
			index++;
		new_node = ft_calloc(index, sizeof(int));
		i = index;
		while (index)
		{
			new_node[index] = ft_atoi(node->content + index);
			index--;
		}
		free(node->content);
		node->content = new_node;
		for (int j = 0; i != j + 1; ++j)
			ft_printf("%4i", ((int *)node->content)[i]);
		node = node->next;
	}
}