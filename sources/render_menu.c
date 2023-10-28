/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:08:45 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/24 01:08:47 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	put_menu_flag(mlx_t *mlx);
static void	put_menu_text(mlx_t *mlx);

void	render_menu(t_data *data)
{
	mlx_put_string(data->mlx, " _______________________________________", 10, 40);
	mlx_put_string(data->mlx, "/                                       \\", 10, 53);
	mlx_put_string(data->mlx, "            42 Sao Paulo - FdF ", 10, 61);
	mlx_put_string(data->mlx, "\\_______________________________________/", 10, 68);
	mlx_put_string(data->mlx, "        _______  ______   _______ ", 10, 90);
	mlx_put_string(data->mlx, "       (  ____ \\(  __  \\ (  ____ \\", 10, 105);
	mlx_put_string(data->mlx, "       | (    \\/| (  \\  )| (    \\/", 10, 120);
	mlx_put_string(data->mlx, "       | (__    | |   ) || (__    ", 10, 135);
	mlx_put_string(data->mlx, "       |  __)   | |   | ||  __)   ", 10, 150);
	mlx_put_string(data->mlx, "       | (      | |   ) || (      ", 10, 165);
	mlx_put_string(data->mlx, "       | )      | (__/  )| )      ", 10, 180);
	mlx_put_string(data->mlx, "       |/       (______/ |/       ", 10, 195);
	mlx_put_string(data->mlx, " _______________________________________", 10, 220);
	mlx_put_string(data->mlx, "/                                       \\", 10, 233);
	mlx_put_string(data->mlx, "                Controls", 10, 241);
	mlx_put_string(data->mlx, "\\_______________________________________/", 10, 248);
	put_menu_flag(data->mlx);
	put_menu_text(data->mlx);
}

void	render_menu_background(mlx_image_t *image)
{
	int x = 0;
	int y = 0;
	while (y <= HEIGHT)
	{
		while (x <= MENU_WIDTH)
		{
			mlx_put_pixel(image, x, y, 0x80008050);
			x++;
		}
		x = 0;
		y++;
	}
}

static void put_menu_flag(mlx_t *mlx)
{
	int y = 265;
	int x = 22;
	while (y < 740)
	{
		mlx_put_string(mlx, "|", 20, y);
		mlx_put_string(mlx, "|", 400, y);
		y += 20;
	}
	while (y < 940)
	{
		mlx_put_string(mlx, "\\", x, y);
		mlx_put_string(mlx, "/", 420 - x, y);
		x += 7;
		y += 18;
	}
	mlx_put_string(mlx, "_______________________", 100, 930);
}

static void put_menu_text(mlx_t *mlx)
{
	mlx_put_string(mlx, "Rotate by X axis -> 'Y' and 'U' keys", 35, 280);
	mlx_put_string(mlx, "Rotate by Y axis -> 'H' and 'J' keys", 35, 300);
	mlx_put_string(mlx, "Rotate by Z axis -> 'N' and 'M' keys", 35, 320);
	mlx_put_string(mlx, "Zoom out -> Scroll down or '-' key", 45, 360);
	mlx_put_string(mlx, "Zoom in -> Scroll up or '+' key", 60, 380);
	mlx_put_string(mlx, "Mirror by X axis -> 'R' and 'T' key", 40, 420);
	mlx_put_string(mlx, "Mirror by Y axis -> 'F' and 'G' key", 40, 440);
	mlx_put_string(mlx, "Centralize -> SPACE key", 100, 480);
	mlx_put_string(mlx, "42 Isometric projection -> '1' key", 60, 520);
	mlx_put_string(mlx, "True isometric projection -> '2' key", 35, 540);
	mlx_put_string(mlx, "Orthographic projection -> '3' key", 55, 560);
	mlx_put_string(mlx, "Stereographic projection -> '4' key", 45, 580);
	mlx_put_string(mlx, "Torus projection -> '5' key", 85, 600);
	mlx_put_string(mlx, "Map color scheme-> 'Z' key", 90, 640);
	mlx_put_string(mlx, "Hendrix color scheme-> 'X' key", 65, 660);
	mlx_put_string(mlx, "Polarity color scheme-> 'C' key", 60, 680);
	mlx_put_string(mlx, "Exit -> ESC key", 150, 720);
}