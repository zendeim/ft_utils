/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memvcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:37:36 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/10 21:31:59 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "libft_io.h"

// Copies different pointers into a linear buffer
// Returns: NULL on full copy, or the mutated vec array for incomplete copies
t_vec	**ft_memvcpy(char **restrict wdst, t_vec **restrict vec, char *end)
{
	const char	*restrict	src;
	char		*restrict	dst;
	size_t					space_left;

	dst = (char *restrict)*wdst;
	while (*vec != NULL)
	{
		src = (const char *restrict)vec[0]->ptr;
		space_left = (size_t)(end - dst);
		if (vec[0]->length < space_left)
			space_left = vec[0]->length;
		vec[0]->length -= space_left;
		while (space_left-- > 0)
			*dst++ = *src++;
		*wdst = dst;
		vec[0]->ptr = src;
		if (dst >= end)
			return (vec);
		vec++;
	}
	return (NULL);
}
