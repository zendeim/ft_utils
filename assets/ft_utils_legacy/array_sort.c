/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:00:59 by adeimlin          #+#    #+#             */
/*   Updated: 2025/06/16 16:25:47 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

void	ft_bubble_sort(int32_t *array, size_t length)
{
	uint_fast8_t	swapped;
	int32_t			temp;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < length - 1 && swapped != 0)
	{
		j = 0;
		swapped = 0;
		while (j < length - i - 1)
		{
			if (array[j + 1] < array[j])
			{
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
				swapped = 1;
			}
			j++;
		}
		i++;
	}
}

void	ft_selection_sort(int32_t *array, size_t length)
{
	int32_t	temp;
	int32_t	*min;
	int32_t	*end;
	int32_t	*ptr;

	end = array + length;
	while (array < end - 1)
	{
		min = array;
		ptr = array + 1;
		while (ptr < end)
		{
			if (*ptr < *min)
				min = ptr;
			ptr++;
		}
		temp = *array;
		*array = *min;
		*min = temp;
		array++;
	}
}

void	ft_insertion_sort(int32_t *array, size_t length)
{
	size_t	i;
	size_t	j;
	int32_t	key;

	i = 1;
	while (i < length)
	{
		j = i;
		key = array[i];
		while (j > 0 && array[j - 1] > key)
		{
			array[j] = array[j - 1];
			j--;
		}
		array[j] = key;
		i++;
	}
}
