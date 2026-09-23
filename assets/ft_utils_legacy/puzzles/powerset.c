/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:06:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/03 15:17:00 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout,
// write

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout,
// write
// ./powerset 5 1 2 3 4 5
// 1 4
// 2 3
// 5

static int32_t	*set;
static uint32_t	*subset;
static int32_t	target;
static size_t	set_size;

// 1 2 3 4 5
// 12 13 14 15 23 24 25 34 35 45
// 123 124 125 134 234 235 345
// 1234 2345
// 12345
static void ft_print(size_t perm_size)
{
	for (size_t i = 0; i < perm_size; i++)
		printf("%d ", set[subset[i]]);
	printf("\n");
}

static int32_t	increment(size_t perm_size)
{
	size_t	i;

	subset[perm_size - 1] += 1;
	i = perm_size - 1;
	while (subset[i] > set_size - (perm_size - i))
	{
		if (i == 0)
			return (0);
		subset[i - 1] += 1;
		i--;
	}
	i++;
	while (i < perm_size)
	{
		subset[i] = subset[i - 1] + 1;
		i++;
	}
	return (1);
}

static inline
void	match_print(size_t perm_size)
{
	int32_t	sum = 0;

	for (size_t i = 0; i < perm_size; i++)
		sum += set[subset[i]];
	if (sum == target)
		ft_print(perm_size);
}

static void find_valid(size_t perm_size)
{
	for (size_t i = 0; i < set_size; i++)
		subset[i] = i;
	while (true)
	{
		match_print(perm_size);
		if (increment(perm_size) == 0)
			break ;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	
	set_size = (size_t)(argc - 2);
	target = atoi(argv[1]);
	if ((set = malloc(2 * set_size * sizeof(int32_t))) == NULL)
		return (1);
	subset = (uint32_t *) set + set_size;
	for (size_t i = 0; i < set_size; i++)
		set[i] = atoi(argv[i + 2]);
	for (size_t i = 0; i < set_size; i++)
		find_valid(i + 1);
	free(set);
	return (0);
}
