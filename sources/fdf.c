/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:52:31 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 01:13:39 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!argv || argc != 2)
		handle_error(ARGUMENTS_ERROR_MESSAGE);
	initialize_data(argv[1], &data);
	handle_mlx(data, argv[1]);
	free_data(data);
	return (EXIT_SUCCESS);
}

void	handle_error(const char *message)
{
	if (errno)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

void	handle_key_hooks(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
	set_render_attributes(data);
	manage_render(data);
}

void	handle_scroll_hook(double scroll_x, double scroll_y, t_data *data)
{
	manage_zoom(scroll_x > 0 || scroll_y > 0, scroll_x < 0 || scroll_y < 0,
		&data->camera->position->z);
	manage_render(data);
}

void	manage_render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->projection = apply_isometric;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_2))
		data->projection = apply_true_isometric;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_3))
		data->projection = NULL;
	render_map(data, apply_bresenham, data->projection);
	render_menu_background(data->image);
}
