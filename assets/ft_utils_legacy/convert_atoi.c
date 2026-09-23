/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/10 12:03:47 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <threads.h>

size_t		ft_strlen(const char *str);
void		*ft_memset(void *vdst, const uint8_t byte, size_t length);

// To do: set errno on overflow
int64_t	ft_strtol(const char *str)
{
	int64_t	number;
	int64_t	sign;

	number = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = -1 + ((*str == '-') << 1);
	str += (sign == 1) || (*str == '+');
	while (*str >= '0' && *str <= '9')
		number = number * 10 - (*str++ - '0');
	return (sign * number);
}

int64_t	ft_strntol(const char *str, size_t length)
{
	const char	*end = str + length;
	int64_t		number;
	int64_t		sign;

	number = 0;
	while (str < end && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	sign = -1 + ((*str == '-') << 1);
	str += (sign == 1) || (*str == '+');
	while (*str >= '0' && *str <= '9' && str < end)
		number = number * 10 - (*str++ - '0');
	return (sign * number);
}

// Decide on naming and check if strlen is higher than overflow
// Open an issue because of uint8_t *
uint64_t	ft_atoi_hex(const char *str)
{
	uint64_t				number;
	static const uint8_t	lut[256] = {
	['0'] = 0, ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4,
	['5'] = 5, ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9,
	['A'] = 10, ['B'] = 11, ['C'] = 12, ['D'] = 13, ['E'] = 14, ['F'] = 15,
	['a'] = 10, ['b'] = 11, ['c'] = 12, ['d'] = 13, ['e'] = 14, ['f'] = 15};

	number = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	str += (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) << 1;
	while (lut[*(const uint8_t *) str] || *str == '0')
		number += (number << 4) + lut[*(const uint8_t *) str++];
	return (number);
}

int64_t	ft_atoi_base(const char *str, const char *base)
{
	size_t			i;
	uint8_t			lookup_table[256];
	int64_t			number;
	const int64_t	radix = (int64_t) ft_strlen(base);
	int64_t			sign;

	ft_memset(lookup_table, 255, 256);
	i = 0;
	while (i < radix)
	{
		lookup_table[(uint8_t) base[i]] = i;
		i++;
	}
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = -1 + ((*str == '-') << 1);
	str += (sign == 1) || (*str == '+');
	number = 0;
	while (lookup_table[*str] != 255)
	{
		number = number * radix - lookup_table[*str];
		str++;
	}
	return (number * sign);
}
