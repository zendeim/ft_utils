/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:57:33 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/08 22:34:39 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "core.h"

int draw_line(u32 *data, size_t stride, int32_t x0, int32_t y0, int32_t x1, int32_t y1, u32 color)
{
	u32		i;
	u32		length;
	int32_t	x, y;
	int64_t	dx, dy;

	length = (u32) ABSMAX(x1 - x0, y1 - y0);
	if (UNLIKELY(length == 0))
		return (-1);
	x0 <<= 16;
	y0 <<= 16;
	x1 <<= 16;
	y1 <<= 16;
	length += (length == 0);
	dx = (x1 - x0) / (int32_t)length;
	dy = (y1 - y0) / (int32_t)length;
	x = x0;
	y = y0;
	for (u32 i = 0; i < length; i++)
	{
		stt_putrgb(&frame, x >> 16, y >> 16, color);
		x += dx;
		y += dy;
	}
}
