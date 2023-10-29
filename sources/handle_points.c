/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 02:38:33 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/29 02:38:40 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	rotate_x(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x;
	new_p.y = p.y * cos(angle) - p.z * sin(angle);
	new_p.z = p.y * sin(angle) + p.z * cos(angle);
	return (new_p);
}

t_point	rotate_y(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x * cos(angle) + p.z * sin(angle);
	new_p.y = p.y;
	new_p.z = -p.x * sin(angle) + p.z * cos(angle);
	return (new_p);
}

t_point	rotate_z(t_point p, double angle)
{
	t_point	new_p;

	new_p.x = p.x * cos(angle) - p.y * sin(angle);
	new_p.y = p.x * sin(angle) + p.y * cos(angle);
	new_p.z = p.z;
	return (new_p);
}

t_point	apply_true_isometric(t_point p)
{
	t_point	new_p;

	new_p.x = (p.x - p.z) / SQRT_2;
	new_p.y = (p.x + (2 * p.y) + p.z) / SQRT_6;
	new_p.z = p.z;
	return (new_p);
}

t_point	apply_isometric(t_point p)
{
	t_point	new_p;

	new_p.x = (p.x - p.y) * COS_0_8;
	new_p.y = (p.x + p.y) * SIN_0_8 - p.z;
	new_p.z = p.z;
	return (new_p);
}
