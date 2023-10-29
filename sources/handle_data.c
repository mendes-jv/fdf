/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:55:36 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/28 23:56:21 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	initialize_data(char *map_path, t_data **data)
{
	*data = ft_calloc(1, sizeof(t_data));
	(*data)->map = parse_map(map_path);
	(*data)->camera = ft_calloc(1, sizeof(t_camera));
	(*data)->camera->position = ft_calloc(1, sizeof(t_point));
	(*data)->camera->rotation = ft_calloc(1, sizeof(t_point));
	(*data)->camera->mirroring = ft_calloc(1, sizeof(t_point));
	(*data)->projection = apply_isometric;
	(*data)->camera->position->x = ((float)WIDTH + (float)MENU_WIDTH) / 2;
	(*data)->camera->position->y = (float)HEIGHT / 2;
	(*data)->camera->position->z = (double)ft_ternary((WIDTH > HEIGHT), WIDTH
			/ (*data)->map->width, HEIGHT / (*data)->map->height) / 3;
	(*data)->camera->rotation->x = 0;
	(*data)->camera->rotation->y = 0;
	(*data)->camera->rotation->z = 0;
	(*data)->camera->mirroring->x = 0;
	(*data)->camera->mirroring->y = 0;
	(*data)->camera->color_mode = DEFAULT_COLOR_MODE;
	(*data)->camera->upscaling = 10;
}

void	free_data(t_data *data)
{
	ft_lstclear(&data->map->list, free);
	free(data->camera->rotation);
	free(data->camera->position);
	free(data->camera->mirroring);
	free(data->camera);
	free(data->map);
	free(data);
}

int	ft_atorgb(const char *str)
{
	int	result;

	result = 0;
	if (!str)
		return (0xFFFFFF);
	if (*str == '0' && *(str + 1) == 'x')
		str += 2;
	while (*str)
	{
		result = result * 16;
		if (*str >= '0' && *str <= '9')
			result += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			result += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			result += *str - 'A' + 10;
		else
			return (0x0);
		str++;
	}
	return (result);
}
