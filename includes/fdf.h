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
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

// MACROS DEFINITIONS
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
#  define PROGRAM_NAME "Fil De Fer"
# endif //PROGRAM_NAME

# ifndef ARGUMENTS_ERROR_MESSAGE
#  define ARGUMENTS_ERROR_MESSAGE "Invalid arguments\nUsage: ./fdf <map.fdf>\n"
# endif //ARGUMENTS_ERROR_MESSAGE

# ifndef OPEN_FAILURE_MESSAGE
#  define OPEN_FAILURE_MESSAGE "Failed to open file"
# endif //OPEN_FAILURE_MESSAGE

# ifndef TWO_DEGREE_IN_RADIAN
#  define TWO_DEGREE_IN_RADIAN 0.034906585
# endif //TWO_DEGREE_IN_RADIAN

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
	t_camera	*camera;
	t_map		*map;
	t_proj_f	projection;
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_data;

typedef void (*t_draw_f)(t_data *, t_proj_f, t_point, t_point);

// FUNCTION PROTOTYPES
t_point	apply_isometric(t_point p);
t_point	apply_true_isometric(t_point p);
void	apply_bresenham(t_data *data, t_proj_f f, t_point p1, t_point p2);
void	handle_error(const char *message);
void	handle_mlx(t_data *data);
void	handle_key_hooks(t_data *data);
void	handle_scroll_hook(double scroll_x, double scroll_y, t_data *data);
t_map	*parse_map(char *map_str);
void	render_map(t_data *data, t_draw_f d_f, t_proj_f p_f);
void	render_menu(t_data *data);
void	render_menu_background(mlx_image_t *mlx);
void	initialize_data(char *map_path, t_data **data);
void	free_data(t_data *data);
size_t	ft_arr_len(char **array);
void	ft_foreach_str(char **array, void (*f)(void *));
void	ft_foreach_array(char ***array, void (*f1)(void *), void (*f2)(void *));
char	***ft_split_array(char **array, char delimiter);
int		ft_atorgb(const char *str);

#endif //FDF_H
