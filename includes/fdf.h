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
# include <fcntl.h>
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

# ifndef PROGRAM_NAME
#  define PROGRAM_NAME "Fil De Fer"
# endif //PROGRAM_NAME

# ifndef ARGUMENTS_ERROR_MESSAGE
#  define ARGUMENTS_ERROR_MESSAGE "Invalid arguments\nUsage: ./fdf <map.fdf>\n"
# endif //ARGUMENTS_ERROR_MESSAGE

# ifndef OPEN_FAILURE_MESSAGE
#  define OPEN_FAILURE_MESSAGE "Failed to open file\n"
# endif //OPEN_FAILURE_MESSAGE

# ifndef EDGE_LENGTH
#  define EDGE_LENGTH 50
# endif //EDGE_LENGTH

// TYPE DEFINITIONS
typedef	struct s_map
{
	t_list	*list;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_data
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;

typedef  struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef t_point (*t_proj_f)(t_point);

typedef void (*t_draw_f)(mlx_image_t *, t_proj_f, t_point, t_point);

// FUNCTION PROTOTYPES
void	handle_error(const char *message);
void	handle_mlx(t_data *data);
t_map	*parse_map(char *map_str);
void	render_map(t_data *data, t_draw_f d_f, t_proj_f p_f);
int		ft_count_if(char **tab, int (*f)(char*));
t_point	isometric(t_point p);
void	bresenham(mlx_image_t *image, t_proj_f f, t_point p1, t_point p2);

#endif //FDF_H
