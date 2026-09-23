/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:21:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 20:49:47 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct
{
	float	x;
	float	y;
}	t_pos;

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
// y - yo = m (x - xo)
float	calc_distance(t_pos a, t_pos b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;

	return (sqrtf(dx * dx + dy * dy));
}

float	calc_seq_dist(size_t *sequence, float best_dist, size_t length, t_pos *pos)
{
	size_t	i;
	float	total_distance = 0.0f;

	i = 1;
	while (i < length)
	{
		total_distance += calc_distance(pos[sequence[i - 1]], pos[sequence[i]]);
		if (total_distance > best_dist)
			return (FLT_MAX);
		i++;
	}
	total_distance += calc_distance(pos[sequence[i]], pos[sequence[0]]);
	return (total_distance);
}

float	get_best_distance(t_pos *pos, size_t length)
{
	size_t	sequence[12];
	float	cur_dist;
	float	best_dist = FLT_MAX;

	for (size_t i = 0; i < 12; i++)
		sequence[i] = i;
	best_dist = calc_seq_dist(sequence, best_dist, length, pos);
	while (next_perm(sequence, length, length))
	{
		cur_dist = calc_seq_dist(sequence, best_dist, length, pos);
		if (cur_dist < best_dist)
			best_dist = cur_dist;
	}
	return (best_dist);
}

int	main(int argc, char **argv, char **envp)
{
	t_pos	pos[12];
	size_t	i;

	i = 0;
	while (i < 12 && fscanf(stdin, "%f, %f\n", &pos[i].x, &pos[i].y) == 2)
		i++;
	printf("%.2f", get_best_distance(pos, i));
	return (0);
}
