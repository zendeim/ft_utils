/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:17:08 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/10 12:07:33 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void	*ft_memset(void *vdst, const uint8_t byte, size_t length);
void	*ft_memcpy(void *restrict vdst, const void *restrict vsrc, size_t len);

// Pointer cast is necessary otherwise caller would need to cast void **
void	**ft_free_array(void *array, size_t length)
{
	if (array == NULL)
		return (NULL);
	while (length-- > 0)
	{
		free(((void **) array)[length]);
		((void **) array)[length] = NULL;
	}
	free(array);
	return (NULL);
}

// See if there is an efficient overflow handling
void	*ft_calloc(size_t arr_size, size_t type_size)
{
	void			*array;
	const size_t	total_size = arr_size * type_size;

	array = (void *) malloc(total_size);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, total_size);
	return (array);
}

// Reallocates memory to a bigger size, copies old array
// If the old array is NULL, this is effectively just malloc
// Always frees the src array
void	*ft_realloc(void *src, size_t src_size, size_t dst_size)
{
	void	*dst;

	dst = (void *) malloc(dst_size);
	if (dst != NULL)
	{
		*((unsigned char *) dst) = 0;
		if (src != NULL)
			ft_memcpy(dst, src, src_size);
	}
	free(src);
	return (dst);
}
