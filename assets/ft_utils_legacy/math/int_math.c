/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:56:46 by adeimlin          #+#    #+#             */
/*   Updated: 2026/06/02 15:23:33 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include "core.h"

size_t	ft_fibonacci(size_t index)
{
	size_t	previous;
	size_t	current;
	size_t	next;

	next = index;
	previous = 0;
	current = 1;
	while (index > 1)
	{
		next = previous + current;
		previous = current;
		current = next;
		index--;
	}
	return (next);
}

bool	ft_isprime(size_t number)
{
	size_t	factor;

	if (number <= 3)
		return (true);
	if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 || number % 7 == 0)
		return (false);
	factor = 11;
	while (factor * factor <= number)
	{
		if (number % factor == 0 || number % (factor + 2) == 0)
			return (false);
		factor += 6;
	}
	return (true);
}

int64_t	ft_sqrt(int64_t number)
{
	int64_t	i;
	int64_t	sqr;

	i = 1;
	while (true)
	{
		sqr = i * i;
		if (sqr == number)
			return (i);
		else if (sqr > number)
			break;
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
	size_t			i = 1;

	if (power == 0)
		number = 1;
	while (i * 2 < power)
	{
		number *= number;
		i *= 2;
	}
	while (i < power)
	{
		number *= base;
		i++;
	}	
	return (number);
}
