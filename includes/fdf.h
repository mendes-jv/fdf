/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:51:52 by jovicto2          #+#    #+#             */
/*   Updated: 2023/09/26 08:52:13 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//Headers
# include "../libraries/libft/includes/libft.h"
# include "../libraries/mlx42/include/MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// MACROS DEFINITIONS
# ifndef ICON_PATH
#  define ICON_PATH "./assets/42.png"
# endif //ICON_PATH

# ifndef WIDTH
#  define WIDTH 1920
# endif //WIDTH

# ifndef HEIGHT
#  define HEIGHT 1080
# endif //HEIGHT

# ifndef MENU_WIDTH
#  define MENU_WIDTH 430
# endif //MENU_WIDTH

# ifndef PROGRAM_NAME
#  define PROGRAM_NAME "Fil De Fer - "
# endif //PROGRAM_NAME

# ifndef ARGUMENTS_ERROR_MESSAGE
#  define ARGUMENTS_ERROR_MESSAGE "\nInvalid arguments: use \"./fdf <map.fdf>\" to run properly\n"
# endif //ARGUMENTS_ERROR_MESSAGE

# ifndef OPEN_FAILURE_MESSAGE
#  define OPEN_FAILURE_MESSAGE "\nFailed to open file"
# endif //OPEN_FAILURE_MESSAGE

#ifndef INVALID_ARGUMENT_MESSAGE
# define INVALID_ARGUMENT_MESSAGE "\nInvalid map: Please provide a valid map with \"<map_name>.fdf\" extension\n"
# endif //INVALID_ARGUMENT_MESSAGE

# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 0.06
# endif //ROTATION_SPEED

# ifndef SIN_0_8
#  define SIN_0_8 0.71735609089952279
# endif //SIN_0_8

# ifndef COS_0_8
#  define COS_0_8 0.69670670934716539
# endif //COS_0_8

# ifndef PI_X_2
#  define PI_X_2 6.2831853071795862
# endif //PI_X_2

# ifndef SQRT_2
#  define SQRT_2 1.4142135623730951
# endif //SQRT_2

# ifndef SQRT_6
#  define SQRT_6 2.4494897427831779
# endif //SQRT_6

# ifndef DEFAULT_COLOR_MODE
# define DEFAULT_COLOR_MODE 0b0
# endif //DEFAULT_COLOR_MODE

# ifndef HENDRIX_COLOR_MODE
# define HENDRIX_COLOR_MODE 0b1
# endif //HENDRIX_COLOR_MODE

# ifndef POLARITY_COLOR_SCHEME
# define POLARITY_COLOR_SCHEME 0b10
# endif //POLARITY_COLOR_SCHEME

// TYPE DEFINITIONS
typedef struct s_values
{
	int	altitude;
	int	color;
}	t_values;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_camera
{
	t_point	*position;
	t_point	*rotation;
	t_point *mirroring;
	char	upscaling;
	char	color_mode;
}	t_camera;

typedef struct s_map
{
	t_list	*list;
	size_t	width;
	size_t	height;
}	t_map;

typedef t_point (*t_proj_f)(t_point);

typedef struct s_data
{
	t_camera		*camera;
	t_map			*map;
	t_proj_f		projection;
	mlx_texture_t	*icon;
	mlx_image_t		*image;
	mlx_t			*mlx;
}	t_data;

typedef void (*t_draw_f)(t_data *, t_proj_f, t_point, t_point);

// FUNCTION PROTOTYPES
t_point	apply_isometric(t_point p);
t_point	apply_true_isometric(t_point p);
void	apply_bresenham(t_data *data, t_proj_f f, t_point p1, t_point p2);
void	handle_error(const char *message);
void	handle_mlx(t_data *data, char *map_path);
void	manage_render(t_data *data);
void	set_render_attributes(t_data *data);
void	manage_zoom(int zoom_in, int zoom_out, double *zoom);
void	manage_color_mode(t_data *data);
void	manage_upscaling(t_data *data);
void	manage_centralization(t_data *data);
void	manage_translation(t_data *data);
void	manage_rotation(t_data *data);
void	manage_mirroring(t_data *data);
t_point rotate_x(t_point p, double angle);
t_point rotate_y(t_point p, double angle);
t_point rotate_z(t_point p, double angle);
void	handle_key_hooks(t_data *data);
void	handle_scroll_hook(double scroll_x, double scroll_y, t_data *data);
t_map	*parse_map(char *map_str);
void	render_map(t_data *data, t_draw_f d_f, t_proj_f p_f);
void	render_menu(t_data *data);
void	render_menu_background(mlx_image_t *mlx);
void	initialize_data(char *map_path, t_data **data);
void	free_data(t_data *data);
int		ft_atorgb(const char *str);
long	ft_ternary(long condition, long a, long b);

#endif //FDF_H
