/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_reverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:28:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/10 09:21:23 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

void	ft_reverse(void *array, size_t length, size_t element_size)
{
	uint8_t	*start;
	uint8_t	*end;

	start = (uint8_t *) array;
	end = start + length - 1;
	while (start < end)
	{
		ft_swap(start, end, element_size);
		start += element_size;
		end -= element_size;
	}
}

void	ft_reverse8(void *array, size_t length)
{
	uint8_t	*start;
	uint8_t	*end;
	uint8_t	buffer;

	start = (uint8_t *) array;
	end = start + length - 1;
	while (start < end)
	{
		buffer = *start;
		*start++ = *end;
		*end-- = buffer;
	}
}

void	ft_reverse32(void *array, size_t length)
{
	uint32_t	*start;
	uint32_t	*end;
	uint32_t	buffer;

	start = (uint32_t *) array;
	end = start + length - 1;
	while (start < end)
	{
		buffer = *start;
		*start++ = *end;
		*end-- = buffer;
	}
}

void	ft_reverse64(void *array, size_t length)
{
	uint64_t	*start;
	uint64_t	*end;
	uint64_t	buffer;

	start = (uint64_t *) array;
	end = start + length - 1;
	while (start < end)
	{
		buffer = *start;
		*start++ = *end;
		*end-- = buffer;
	}
}
