/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:52:31 by jovicto2          #+#    #+#             */
/*   Updated: 2023/10/20 08:52:28 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv) {
	t_data	*data;

	data = NULL;
	if (!argv || argc != 2)
		handle_error(ARGUMENTS_ERROR_MESSAGE);
	initialize_data(argv[1], &data);
	handle_mlx(data);
	free_data(data);
	return (EXIT_SUCCESS);
}

int	ft_count_if(char **array, size_t (*f)(const char*))
{
	int	count;

	count = 0;
	while (*array)
		if (f(*(array++)))
			count++;
	return (count);
} //TODO: remove this function

void	ft_foreach_str(char **array, size_t length, void (*f)(char *))
{
	while (length--)
		f(*(array++));
} //TODO: remove this function
