/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:33:44 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/28 23:56:23 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char	*parse_program_name(char *map_path);

void	handle_mlx(t_data *data, char *map_path)
{
	char	*window_title;

	mlx_set_setting(MLX_MAXIMIZED, true);
	window_title = parse_program_name(map_path);
	data->mlx = mlx_init(WIDTH, HEIGHT, window_title, true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->icon = mlx_load_png(ICON_PATH);
	mlx_set_icon(data->mlx, data->icon);
	if (!data->mlx || !data->image || mlx_image_to_window(data->mlx,
			data->image, 0, 0) == -1)
	{
		if (data->mlx)
			mlx_close_window(data->mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	render_menu(data);
	mlx_scroll_hook(data->mlx, (mlx_scrollfunc)handle_scroll_hook, data);
	mlx_loop_hook(data->mlx, (void *)handle_key_hooks, data);
	mlx_loop(data->mlx);
	free(window_title);
	mlx_delete_texture(data->icon);
	mlx_terminate(data->mlx);
}

static char	*parse_program_name(char *map_path)
{
	char	*window_title;

	window_title = ft_strrchr(map_path, '/');
	if (!window_title)
		window_title = ft_strjoin(PROGRAM_NAME, map_path);
	else
		window_title = ft_strjoin(PROGRAM_NAME, window_title + 1);
	return (window_title);
}
