/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_bresenham.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:12:04 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 03:12:33 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	get_color(t_data *data, long *color, t_point p1, t_point p2);
static void	apply_modifiers_before_proj(t_data *data, t_point *p1, t_point *p2);
static void	apply_projection(t_proj_f p_f, t_point *p1, t_point *p2);
static void	apply_modifiers_after_proj(t_data *data, t_point *p1, t_point *p2);

void	apply_bresenham(t_data *data, t_proj_f p_f, t_point p1, t_point p2)
{
	double	x_ratio;
	double	y_ratio;
	double	bigger_axis;
	long	color;

	if ((!p1.color && !p1.z) || (!p2.color && !p2.z))
		return ;
	get_color(data, &color, p1, p2);
	apply_modifiers_before_proj(data, &p1, &p2);
	apply_projection(p_f, &p1, &p2);
	apply_modifiers_after_proj(data, &p1, &p2);
	x_ratio = p2.x - p1.x;
	y_ratio = p2.y - p1.y;
	bigger_axis = fmax(fabs(x_ratio), fabs(y_ratio));
	x_ratio /= bigger_axis;
	y_ratio /= bigger_axis;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		if ((int)p1.x < WIDTH && (int)p1.y < HEIGHT && (int)p1.x > MENU_WIDTH
			&& (int)p1.y >= 0)
			mlx_put_pixel(data->image, (uint32_t)p1.x, (uint32_t)p1.y, color);
		p1.x += x_ratio;
		p1.y += y_ratio;
	}
}

static void	apply_modifiers_before_proj(t_data *data, t_point *p1, t_point *p2)
{
	if (p1->z)
		p1->z *= (float)data->camera->upscaling / 10;
	if (p2->z)
		p2->z *= (float)data->camera->upscaling / 10;
	p1->x -= (float)(data->map->width - 1) / 2;
	p1->y -= (float)(data->map->height - 1) / 2;
	p2->x -= (float)(data->map->width - 1) / 2;
	p2->y -= (float)(data->map->height - 1) / 2;
	p1->x *= data->camera->position->z;
	p1->y *= data->camera->position->z;
	p1->z *= data->camera->position->z / 5;
	p2->x *= data->camera->position->z;
	p2->y *= data->camera->position->z;
	p2->z *= data->camera->position->z / 5;
	*p1 = rotate_x(*p1, data->camera->rotation->x);
	*p2 = rotate_x(*p2, data->camera->rotation->x);
	*p1 = rotate_y(*p1, data->camera->rotation->y);
	*p2 = rotate_y(*p2, data->camera->rotation->y);
	*p1 = rotate_z(*p1, data->camera->rotation->z);
	*p2 = rotate_z(*p2, data->camera->rotation->z);
}

static void	apply_modifiers_after_proj(t_data *data, t_point *p1, t_point *p2)
{
	if (data->camera->mirroring->x)
	{
		*p1 = rotate_x(*p1, M_PI);
		*p2 = rotate_x(*p2, M_PI);
	}
	if (data->camera->mirroring->y)
	{
		*p1 = rotate_y(*p1, M_PI);
		*p2 = rotate_y(*p2, M_PI);
	}
	p1->x += data->camera->position->x;
	p2->x += data->camera->position->x;
	p1->y += data->camera->position->y;
	p2->y += data->camera->position->y;
}

static void	get_color(t_data *data, long *color, t_point p1, t_point p2)
{
	*color = (long)ft_ternary(fabs(p1.z) > fabs(p2.z), (long)p1.z, (long)p2.z);
	if (data->camera->color_mode == DEFAULT_COLOR_MODE)
		*color = ft_ternary(*color == (long)p1.z, p1.color, p2.color)
			* 0x100 | 0xFF;
	else if (data->camera->color_mode == HENDRIX_COLOR_MODE)
		*color = ft_ternary(*color,
				ft_ternary(*color > 0 && *color <= 3, 0xD16AFFFF, \
					ft_ternary(*color > 3 && *color <= 5, 0xBB44F0FF, \
					ft_ternary(*color > 5 && *color <= 15, 0x9614D0FF, \
					ft_ternary(*color > 15 && *color <= 25, 0x660094FF, \
					ft_ternary(*color > 25, 0x310047FF, \
					ft_ternary(*color < 0 && *color >= -3, 0xFFFB05FF, \
					ft_ternary(*color < -3 && *color >= -5, 0xFFE505FF, \
					ft_ternary(*color < -5 && *color >= -15, 0xFFC905FF, \
					ft_ternary(*color < -15 && *color >= -25, 0xFFB805FF, \
					0xFFA505FF))))))))), 0xE8B382FF);
	else if ((data)->camera->color_mode == POLARITY_COLOR_SCHEME)
		*color = ft_ternary(*color,
				ft_ternary(*color > 0, 0xB82230FF, 0x1C24D0FF), 0xFFFFFFFF);
}

static void	apply_projection(t_proj_f p_f, t_point *p1, t_point *p2)
{
	if (p_f)
	{
		*p1 = p_f(*p1);
		*p2 = p_f(*p2);
	}
}
