/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:19:24 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/08 22:45:06 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "core.h"

size_t  ft_bitfind(const size_t *word, size_t start, size_t end, bool bit)
{
	size_t			i;
	size_t			offset;
	const size_t	start_mask = SIZE_MAX >> (start % WORD_BITS);
	const size_t	invert = (size_t)-(!bit);
	const size_t	word_end = (end - 1) / WORD_BITS;

	i = start / WORD_BITS;
	offset = (word[i] ^ invert) & start_mask;
	while (offset == 0 && i < word_end)
		offset = word[++i] ^ invert;
	offset = i * WORD_BITS + CLZ(offset);
	if (offset >= end)
		return (SIZE_MAX);
	return (offset);
}

void	ft_bitset(size_t *bitmap, size_t start, size_t end, bool bit)
{
	const size_t	fill = (size_t)-(bit != 0);
	const size_t	start_mask = SIZE_MAX >> (start % WORD_BITS);
	const size_t	end_mask = SIZE_MAX << (-end % WORD_BITS);
	size_t			mask;
	size_t			diff_mask;

	start = start / WORD_BITS;
	end = (end - 1) / WORD_BITS;
	diff_mask = (size_t)-(start != end);
	mask = start_mask & (end_mask | diff_mask);
	bitmap[start] ^= (bitmap[start] ^ fill) & mask;
	start = start + 1;
	while (start < end)
		bitmap[start++] = fill;
	mask = end_mask & diff_mask;
	bitmap[end] ^= (bitmap[end] ^ fill) & mask;
}

