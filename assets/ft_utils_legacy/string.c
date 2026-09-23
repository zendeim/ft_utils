/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/08 22:38:40 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>
#include <threads.h>

// This function fills a buffer with up to 24 ascii digits and null terminates
// Returns the length of the number
size_t	ft_itoa_r(int64_t number, char *ptr)
{
	char	buffer[24];
	int64_t	sign = number >= 0 ? 1 : -1;
	size_t	length;
	size_t	i = sizeof(buffer) - 1;

	buffer[i] = 0;
	buffer[--i] = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		buffer[--i] = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		buffer[--i] = '-';
	length = sizeof(buffer) - i; // Copies \0
	memcpy(ptr, buffer + i, length);
	return (length - 1);
}

uint32_t	ft_strtoargb(const char *str, const char **str_ptr)
{
	size_t		i;
	uint32_t	argb_value;
	int64_t		number;

	i = 0;
	argb_value = 0;
	while (i < 4)
	{
		number = (uint8_t)strtol(str, &str, 10);
		argb_value = (argb_value << 8) + (uint32_t) number;
		i++;
		if (*str != ',')
			break ;
		str++;
	}
	if (i < 3)
		str = NULL;
	if (str_ptr != NULL)
		*str_ptr = str;
	return (argb_value);
}
