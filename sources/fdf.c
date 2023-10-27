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

size_t	ft_arr_len(char **array)
{
	size_t	count;

	count = 0;
	while (*(array++))
		count++;
	return (count);
} //TODO: remove this function

void	ft_for_each(void **array, void (*f)(void *))
{
	while (*array)
		f(*(array++));
} //TODO: remove this function

void	ft_array_for_each(void **array, void (*array_f)(void *), void (*index_f)(void *))
{
	while (*array)
	{
		ft_for_each(*array, index_f);
		array_f(*(array++));
	}
} //TODO: remove this function

char	***ft_split_array(char **array, char delimiter)
{
	char	***split_array;
	size_t	length;

	length = ft_arr_len(array);
	split_array = ft_calloc(length + 1, sizeof(char **));
	split_array[length] = NULL;
	while (length--)
		split_array[length] = ft_split(array[length], delimiter);
	return (split_array);
} //TODO: remove this function

int	ft_atorgb(const char *str)
{
	int result;

	result = 0;
	if(!str)
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
} //TODO: Change this (*str) to don't use so many times

int ft_ternary(int condition, int a, int b)
{
	if (condition)
		return (a);
	return (b);
} //TODO: remove this function