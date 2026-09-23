/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nqueens2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:08:32 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 18:45:47 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static inline
void	set_lut(size_t *lut, size_t *perm, size_t length, size_t max_size)
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
	size_t	lut[64];

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
	size_t	lut[64];
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

bool	check_seq(size_t *seq, size_t length)
{
	size_t	x = 0;
	size_t	y = 0;

	while (x < length)
	{
		y = 0;
		while (y < x)
		{
			if (x != y)
			{
				if (seq[x] == seq[y])
					return (false);
				if ((seq[x] - seq[y] == x - y) || (seq[x] - seq[y] == y - x))
					return (false);
			}
			y++;
		}
		x++;
	}
	return (true);
}

void	ft_print(size_t *sequence, size_t length)
{
	for (size_t i = 0; i < length - 1; i++)
	{
		fprintf(stdout, "%zu ", sequence[i]);
	}
	fprintf(stdout, "%zu \n", sequence[length - 1]);
}

int	main(int argc, char **argv, char **envp)
{
	// if (argc != 2)
	// 	return (write(1, "\n", 1), 1);
	// size_t 	length = (size_t) atoi(argv[1]);
	size_t	length = 3;
	size_t	buffer[64];

	for (size_t i = 0; i < 64; i++)
		buffer[i] = i;
	while (true)
	{
		if (check_seq(buffer, length))
			ft_print(buffer, length);
		if (next_perm(buffer, length, length) == false)
			break ;
	}
	return (0);
}
