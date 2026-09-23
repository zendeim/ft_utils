/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:30:38 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/08 22:39:59 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cub_structs.h"
#include "cub_utils.h"

static inline
void	stt_putrgb(t_mat32 *frame, int32_t x, int32_t y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= frame->width || y >= frame->height)
		return ;
	frame->ptr[frame->stride * x + y] = color;
}

void	draw_circle(t_mat32 frame, t_quad quad)
{
	int32_t		y;
	int32_t		x;
	t_vec2		dst;
	uint32_t	color;

	y = 0;
	while (y <= quad.size.y.i)
	{
		x = 0;
		while (x <= quad.size.x.i)
		{
			dst.x.i = quad.pos.x.i + x;
			dst.y.i = quad.pos.y.i + y;
			color = ((uint32_t)ft_rand() & 0x0F0F0Fu) ^ quad.color;
			if (dst.x.i >= 0 && dst.y.i >= 0
				&& dst.x.i < frame.width && dst.y.i < frame.height
				&& vec2_idist(quad.center, dst) <= quad.radius * quad.radius)
				frame.ptr[dst.x.i * frame.stride + dst.y.i] = color;
			x++;
		}
		y++;
	}
}
