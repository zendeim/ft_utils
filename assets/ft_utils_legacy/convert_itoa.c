/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:42:14 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/11 23:36:43 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <threads.h>
#include <stdlib.h>
#include <stdbool.h>

char		*ft_strdup(const char *src);
size_t		ft_strlen(const char *str);

char	*ft_itoa(int64_t number)
{
	size_t			i;
	char			array[24];
	const int8_t	sign = (number >= 0) - (number < 0);
	char			*ptr;
	char			*str;

	ptr = array + 23;
	*ptr = 0;
	*(--ptr) = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		*(--ptr) = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		*(--ptr) = '-';
	return (ft_strdup(ptr));
}

// This function fills a buffer with up to 24 ascii digits and null terminates
// Returns the length of the number
size_t	ft_itoa_r(int64_t number, char *ptr)
{
	char			buffer[24];
	char			*wptr;
	const int8_t	sign = (number >= 0) - (number < 0);
	const char		*optr = ptr;
	size_t			length;

	wptr = buffer + sizeof(buffer) - 1;
	*wptr = 0;
	*(--wptr) = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		*(--wptr) = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		*(--wptr) = '-';
	length = (size_t)((buffer + sizeof(buffer)) - wptr); // Copies \0
	while (length > 0)
	{
		*ptr++ = *wptr++;
		length--;
	}
	return ((size_t)(ptr - optr) - 1);
}

// Returned result is not re_entrant
char	*ft_itoa_stt(int64_t number)
{
	static thread_local char	buffer[24];
	char						*ptr;
	const int8_t				sign = (number >= 0) - (number < 0);

	ptr = buffer + 23;
	*ptr = 0;
	*(--ptr) = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		*(--ptr) = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		*(--ptr) = '-';
	return (ptr);
}

// TODO
char	*ft_itoa_hex(int64_t number, bool upper_case)
{
	static const char		lut[2][16] = {{'0', '1', '2', '3', '4', '5', '6',
		'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}, {'0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}};
	const bool				sign = number < 0;
	char					str[24];
	char					*ptr;
	uint64_t				abs_num;

	if (sign == true)
		abs_num = (uint64_t)(-number);
	else
		abs_num = (uint64_t) number; 
	ptr = str + 23;
	*ptr = 0;
	*(--ptr) = lut[upper_case][(abs_num & 0xF)];
	abs_num >>= 4;
	while (abs_num != 0)
	{
		*(--ptr) = lut[upper_case][(abs_num & 0xF)];
		abs_num >>= 4;
	}
	if (sign != 0)
		*(--ptr) = '-';
	return (ft_strdup(ptr));
}

char	*ft_itoa_base(int64_t number, const char *base)
{
	const int64_t	sign = (number >> 63);
	const uint64_t	radix = (uint64_t) ft_strlen(base);
	char			str[72];
	char			*ptr;
	uint64_t		abs_num;

	if (radix < 2)
		return (NULL);
	abs_num = (uint64_t)((number ^ sign) - sign);
	ptr = str + 71;
	*ptr = 0;
	*(--ptr) = base[(abs_num % radix)];
	abs_num /= radix;
	while (abs_num != 0)
	{
		*(--ptr) = base[(abs_num % radix)];
		abs_num /= radix;
	}
	if (sign != 0)
		*(--ptr) = '-';
	return (ft_strdup(ptr));
}
