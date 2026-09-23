/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:31:46 by adeimlin          #+#    #+#             */
/*   Updated: 2025/06/13 16:19:27 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubble_sort(void *array_void, size_t array_size, size_t data_size)
{
	int8_t			swapped;
	unsigned char	*end;
	unsigned char	*temp;
	unsigned char	*array;

	swapped = 1;
	array = (unsigned char *) array_void;
	end = (unsigned char *) array_void + data_size * array_size - data_size;
	while (array < end && swapped != 0)
	{
		swapped = 0;
		temp = array;
		while (temp < end)
		{
			if (ft_memrcmp(temp, temp + data_size, data_size) > 0)
			{
				ft_gswap(temp, temp + data_size, data_size);
				swapped = 1;
			}
			temp += data_size;
		}
		end -= data_size;
	}
}

void	ft_reverse(void *array_void, size_t size)
{
	unsigned char	*start;
	unsigned char	*end;
	unsigned char	buffer;

	start = (unsigned char *) array_void;
	end = start + size - 1;
	while (start < end)
	{
		buffer = *start;
		*start = *end;
		*end = buffer;
		start++;
		end--;
	}
}

int main()
{
	int32_t array[] = {1, 3, 4, 2, 1, 6, 8};
	int32_t n = sizeof(array)/sizeof(int32_t);
	ft_bubble_sort(array, n, sizeof(int32_t));

	for (int i=0; i < n; i++)
		printf("%d, ", array[i]);
}
