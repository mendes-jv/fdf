/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:52:31 by jovicto2          #+#    #+#             */
/*   Updated: 2023/09/26 08:56:45 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv) {
	t_data	*data;

	if (!argv || argc != 2)
		handle_error(ARGUMENTS_ERROR_MESSAGE);
	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(MALLOC_FAILURE_MESSAGE);
	data->map = parse_map(argv[1]);
	handle_mlx(data);
	return (EXIT_SUCCESS);
}
