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

# include "../libraries/libft/includes/libft.h"
# include "../libraries/mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

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

void	handle_error(const char *message);
void	handle_mlx(t_data *data);
t_map	*parse_map(char *map_str);
void	render_map(t_data *data);
int		ft_count_if(char **tab, int (*f)(char*));

#endif //FDF_H
