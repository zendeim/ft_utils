/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:59:39 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 21:14:11 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

static inline
void	set_lut(uint8_t *lut, size_t *perm, size_t length, size_t max_size)
{
	size_t	i;

	i = 0;
	while (i < max_size)
	{
		lut[i] = 0;
		i++;
	}
	i = 0;
	while (i < length)
	{
		lut[perm[i]] = 1;
		i++;
	}
}

static
void	overflow_fix(size_t *perm, size_t digit_pos, size_t perm_size, size_t max_size)
{
	size_t	i;
	size_t	j;
	uint8_t	lut[32];

	set_lut(lut, perm, digit_pos, max_size);
	i = digit_pos;
	while (i < perm_size)
	{
		j = 0;
		while (lut[j] == 1)
			j++;
		lut[j] = 1;
		perm[i] = j;
		i++;
	}
}

static
size_t	get_next_value(size_t *perm, size_t digit_pos, size_t max_size)
{
	uint8_t	lut[32];
	size_t	number;

	number = perm[digit_pos] + 1;
	set_lut(lut, perm, digit_pos, max_size);
	while(lut[number] == 1)
		number++;
	return (number);
}

bool	next_perm(size_t *perm, size_t perm_size, size_t max_size)
{
	size_t	i;

	i = perm_size - 1;
	perm[i] = get_next_value(perm, i, max_size);
	while (perm[i] >= max_size)
	{
		if (i == 0)
			return (false);
		i--;
		perm[i] = get_next_value(perm, i, max_size);
	}
	overflow_fix(perm, i + 1, perm_size, max_size);
	return (true);
}

bool	next_comb(size_t *comb, size_t comb_size, size_t max_size)
{
	size_t	i;

	i = comb_size - 1;
	comb[i]++;
	while (comb[i] > max_size - (comb_size - i))
	{
		if (i == 0)
			return (false);
		comb[i - 1] += 1;
		i--;
	}
	i++;
	while (i < comb_size)
	{
		comb[i] = comb[i - 1] + 1;
		i++;
	}
	return (true);
}

bool	next_num(size_t *comb, size_t comb_size, size_t max_size)
{
	size_t	i;

	i = comb_size - 1;
	comb[i]++;
	while (comb[i] > max_size)
	{
		if (i == 0)
			return (false);
		comb[i - 1] += 1;
		i--;
	}
	i++;
	while (i < comb_size)
	{
		comb[i] = 0;
		i++;
	}
	return (true);
}

// static void ft_print(size_t *ptr, size_t length)
// {
// 	for (size_t i = 0; i < length; i++)
// 		printf("%zu ", ptr[i]);
// 	printf("\n");
// }

// int main()
// {
// 	size_t	buffer[64];
// 	size_t length = 3;
// 	size_t max_size = 1;

// 	for (size_t i = 0; i < 64; i++)
// 		buffer[i] = 0;
// 	// ft_print(buffer, length);
// 	while (next_perm(buffer, length, max_size))
// 		;
// 		// ft_print(buffer, length);
// }
