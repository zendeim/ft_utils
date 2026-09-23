/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:30:05 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:13 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft_math.h"

// Create dot product function
void	ft_matmult(const t_matrix *ma, const t_matrix *mb, t_matrix *mc)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;
	float		sum;

	i = 0;
	while (i < mc->rows)
	{
		j = 0;
		while (j < mc->cols)
		{
			sum = 0.0f;
			k = 0;
			while (k < ma->cols)
			{
				sum += ma->data[i * ma->cols + k] * mb->data[k * mb->cols + j];
				k++;
			}
			mc->data[i * mc->cols + j] = sum;
			j++;
		}
		i++;
	}
}

static
t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	size_t	i;
	t_mat4	result;

	i = 0;
	while (i < 4)
	{
		result.row[i].x = a.row[i].x * b.row[0].x + a.row[i].y * b.row[1].x
			+ a.row[i].z * b.row[2].x + a.row[i].w * b.row[3].x;
		result.row[i].y = a.row[i].x * b.row[0].y + a.row[i].y * b.row[1].y
			+ a.row[i].z * b.row[2].y + a.row[i].w * b.row[3].y;
		result.row[i].z = a.row[i].x * b.row[0].z + a.row[i].y * b.row[1].z
			+ a.row[i].z * b.row[2].z + a.row[i].w * b.row[3].z;
		result.row[i].w = a.row[i].x * b.row[0].w + a.row[i].y * b.row[1].w
			+ a.row[i].z * b.row[2].w + a.row[i].w * b.row[3].w;
		i++;
	}
	return (result);
}
