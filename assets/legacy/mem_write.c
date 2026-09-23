/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:35:52 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/02 10:39:32 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

static
void	*stt_memrcpy(void *vdst, const void *vsrc, size_t length)
{
	char		*dst;
	const char	*src = (const char *) vsrc + length;

	if ((uintptr_t) vdst == (uintptr_t) vsrc)
		return (vdst);
	dst = ((char *) vdst) + length;
	while (length > sizeof(uintptr_t)
		&& (((uintptr_t)dst | (uintptr_t)src) & (sizeof(uintptr_t) - 1)))
	{
		*--dst = *--src;
		length--;
	}
	while (length >= sizeof(uintptr_t))
	{
		dst -= sizeof(uintptr_t);
		src -= sizeof(uintptr_t);
		length -= sizeof(uintptr_t);
		*((uintptr_t *)dst) = *((const uintptr_t *)src);
	}
	while (length > 0)
	{
		*--dst = *--src;
		length--;
	}
	return (vdst);
}

void	*ft_memmove(void *vdst, const void *vsrc, size_t length)
{
	char		*dst;
	const char	*src = (const char *) vsrc;

	if ((uintptr_t) vdst >= (uintptr_t) vsrc)
		return (stt_memrcpy(vdst, vsrc, length));
	dst = (char *) vdst;
	while (length > sizeof(uintptr_t)
		&& (((uintptr_t)dst | (uintptr_t)src) & (sizeof(uintptr_t) - 1)))
	{
		*dst++ = *src++;
		length--;
	}
	while (length >= sizeof(uintptr_t))
	{
		*((uintptr_t *)dst) = *((const uintptr_t *)src);
		dst += sizeof(uintptr_t);
		src += sizeof(uintptr_t);
		length -= sizeof(uintptr_t);
	}
	while (length > 0)
	{
		*dst++ = *src++;
		length--;
	}
	return (vdst);
}

void	*ft_memcpy(void *vdst, const void *vsrc, size_t length)
{
	unsigned char	 *dst;
	const unsigned char *src = vsrc;

	dst = vdst;
	while (length > 0)
	{
		*dst++ = *src++;
		length--;
	}
	return (vdst);
}

void	*ft_bzero(void *dst_void, size_t length)
{
	uint8_t	*dst;

	dst = (uint8_t *) dst_void;
	while (((uintptr_t)dst & (sizeof(uintptr_t) - 1)) && length > 0)
	{
		*dst++ = 0u;
		length--;
	}
	while (length >= sizeof(uintptr_t))
	{
		*((uintptr_t *)dst) = 0UL;
		dst += sizeof(uintptr_t);
		length -= sizeof(uintptr_t);
	}
	while (length > 0)
	{
		*dst++ = 0u;
		length--;
	}
	return (dst_void);
}

void	*ft_memset(void *vdst, const uint8_t byte, size_t length)
{
	uint8_t			*dst;
	const uintptr_t	word_byte = byte * (0x0101010101010101 & UINTPTR_MAX);

	dst = (uint8_t *) vdst;
	while (((uintptr_t)dst & (sizeof(uintptr_t) - 1)) && length > 0)
	{
		*dst++ = byte;
		length--;
	}
	while (length >= sizeof(uintptr_t))
	{
		*((uintptr_t *)dst) = word_byte;
		dst += sizeof(uintptr_t);
		length -= sizeof(uintptr_t);
	}
	while (length > 0)
	{
		*dst++ = byte;
		length--;
	}
	return (vdst);
}
