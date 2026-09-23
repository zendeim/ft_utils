/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:59:40 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/08 22:55:08 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

void	ft_i32v(int32_t *array, size_t length, int32_t *min, int32_t *max)
{
	size_t	i;

	*min = array[0];
	*max = array[0];
	i = 1;
	while (i < length)
	{
		if (array[i] < *min)
			*min = array[i];
		if (array[i] > *max)
			*max = array[i];
		i++;
	}
}

void	ft_i32p(int32_t *array, size_t length, size_t *min, size_t *max)
{
	size_t	i;

	*min = 0;
	*max = 0;
	i = 1;
	while (i < length)
	{
		if (array[i] < array[*min])
			*min = i;
		if (array[i] > array[*max])
			*max = i;
		i++;
	}
}

// give this a god damn name
void	ft_i64v(int64_t *array, size_t length, int64_t *min, int64_t *max)
{
	size_t	i;

	*min = array[0];
	*max = array[0];
	i = 1;
	while (i < length)
	{
		if (array[i] < *min)
			*min = array[i];
		if (array[i] > *max)
			*max = array[i];
		i++;
	}
}

void	ft_i64p(int64_t *array, size_t length, size_t *min, size_t *max)
{
	size_t	i;

	*min = 0;
	*max = 0;
	i = 1;
	while (i < length)
	{
		if (array[i] < array[*min])
			*min = i;
		if (array[i] > array[*max])
			*max = i;
		i++;
	}
}
