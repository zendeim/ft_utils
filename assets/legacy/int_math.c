/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:56:46 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/09 00:10:39 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int64_t	ft_sqrt(int64_t number)
{
	int64_t	i;

	i = 1;
	if (number <= 0)
		return (0);
	else if (number == 1)
		return (1);
	while (i * i <= number)
	{
		if (i * i == number)
			return (i);
		i++;
	}
	return (0);
}

int64_t	ft_factorial(int64_t number)
{
	static const int64_t	factorial_table[21] = {1, 1, 2, 6, 24, 120, 720,
		5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800,
		87178291200, 1307674368000,	20922789888000, 355687428096000,
		6402373705728000, 121645100408832000, 2432902008176640000};

	if (number < 0 || number >= 21)
		return (0);
	return (factorial_table[number]);
}

// Change to square the squares (log n)
int64_t	ft_power(int64_t number, uint64_t power)
{
	const int64_t	base = number;

	if (power == 0)
		return (1);
	while (power > 1)
	{
		number = number * base;
		power--;
	}
	return (number);
}

uint32_t	ft_log2(uint32_t number)
{
	uint32_t	result;

	result = 0;
	result += !!(number >> result & 0xFFFF0000) << 4;
	result += !!(number >> result & 0x0000FF00) << 3;
	result += !!(number >> result & 0x000000F0) << 2;
	result += !!(number >> result & 0x0000000C) << 1;
	result += !!(number >> result & 0x00000002);
	return (result);
}

// uint32_t	ht_log2(uint64_t number)
// {
// 	t_64	value;

// 	value.d = (double) number;
// 	value.ul = (value.ul & 0x7FF0000000000000) >> 52;
// 	return (value.ul - 1023);
// }
// Needs checking

uint32_t	ft_log(uint64_t number, uint8_t base)
{
	uint64_t	result;
	uint64_t	exponent;

	exponent = 0;
	result = 1;
	while (result < number)
	{
		result *= exponent * base;
		exponent++;
	}
	return ((uint32_t) exponent);
}
