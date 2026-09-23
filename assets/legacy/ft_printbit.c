/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:28:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/06/13 19:28:31 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

// 10000000 01000000 00100000 00010000 00001000 00000100 00000010 00000001

void	print_bits(const uint8_t byte)
{
	uint64_t expand;

	expand = (((uint64_t)byte * 0x8040201008040201ULL) >> 7);
	expand = (expand & 0x0101010101010101ULL) | 0x3030303030303030ULL;
	write(1, &expand, 8);
}

void	print_bits2(const uint8_t byte)
{
	uint64_t x = byte;

	x = (x & 0x80) << 49 | (x & 0x40) << 42 | (x & 0x20) << 35 
	| (x & 0x10) << 28 | (x & 0x08) << 21 | (x & 0x04) << 14 
	| (x & 0x02) << 7 | (x & 0x01);
	x |= 0x3030303030303030ULL;
	write(1, &x, 8);
}

static void	print_bits3(const uint8_t byte)
{
	unsigned char	buffer[8];

	buffer[0] = !!(byte & 0x01) + '0';
	buffer[1] = !!(byte & 0x02) + '0';
	buffer[2] = !!(byte & 0x04) + '0';
	buffer[3] = !!(byte & 0x08) + '0';
	buffer[4] = !!(byte & 0x10) + '0';
	buffer[5] = !!(byte & 0x20) + '0';
	buffer[6] = !!(byte & 0x40) + '0';
	buffer[7] = !!(byte & 0x80) + '0';
	write(1, buffer, 8);
}

// 10000000 01000000 00100000 00010000 00001000 00000100 00000010 10000001
static void	print_bits_loop(uint8_t byte)
{
	unsigned char	buffer[8];
	uint_fast8_t	i;

	i = 8;
	while (i > 0)
	{
		buffer[--i] = (byte & 0x01) + '0';
		byte >>= 1;
	}
	write(1, buffer, 8);
}

static void	print_bits_table(uint8_t byte)
{
    static const uint32_t	nibble[16] = {0x30303030, 0x30303031, 0x30303130, 0x30303131,
		0x30313030, 0x30313031, 0x30313130, 0x30313131, 0x31303030, 0x31303031,
		0x31303130, 0x31303131, 0x31313030, 0x31313031, 0x31313130, 0x31313131};
	const uint64_t			x = ((uint64_t)nibble[byte >> 4] << 32) | nibble[byte & 0x0F];

	write(1, &x, 8);
}

int main()
{
	print_bits2(0b00100110);
}