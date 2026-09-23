/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:24:42 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/10 17:23:12 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

const char	**ft_strvcpy(char **restrict wdst,
	const char **restrict vec, char *restrict end);

#ifndef FT_IO_BUFSIZE
# define FT_IO_BUFSIZE 4096
#endif

// endl is the character to print in place of null terminator
// For endl to work, string must not be read-only (endl = 0 normal behavior)
ssize_t	ft_putstr(int fd, char *str, char endl)
{
	ssize_t		bytes;
	const char	*ostr = str;
	size_t		length;

	if (str == NULL)
		return (write(fd, "(null)", 6));
	while (*str != 0)
		str++;
	length = str - ostr;
	if (endl == 0)
		return (write(fd, ostr, length));
	str[length] = endl;
	bytes = write(fd, ostr, length + 1);
	str[length] = 0;
	return (bytes);
}

ssize_t	ft_putstrv(int fd, const char **vec, char endl)
{
	char		buffer[FT_IO_BUFSIZE];
	ssize_t		bytes_written;
	ssize_t		bytes_total;
	const char	**src = vec;
	char		*dst;

	if (vec == NULL || *vec == NULL)
		return (-1);
	bytes_total = 0;
	dst = buffer;
	src = ft_strvcpy(&dst, src, buffer + FT_IO_BUFSIZE);
	while (src != NULL)
	{
		bytes_written = write(fd, buffer, (size_t)(dst - buffer));
		if (bytes_written < 0)
			return (-1);
		bytes_total += bytes_written;
		dst = buffer;
		src = ft_strvcpy(&dst, src, buffer + FT_IO_BUFSIZE);
	}
	dst[-1] = endl;
	bytes_written = write(fd, buffer, (size_t)(dst - buffer - (endl == 0)));
	if (bytes_written < 0)
		return (-1);
	return (bytes_total + bytes_written);
}

ssize_t	ft_putnbr(int fd, int64_t number)
{
	const int64_t	sign = (number >= 0) - (number < 0);
	char			buffer[24];
	char			*ptr;

	ptr = buffer + 23;
	*(ptr) = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		*(--ptr) = (number % 10) + '0';
		number /= 10;
	}
	if (sign < 0)
		*(--ptr) = '-';
	return (write(fd, ptr, 24 - (size_t)(ptr - buffer)));	// Check
}

ssize_t	ft_putnchar(int fd, char c, size_t length)
{
	ssize_t		bytes;
	const char	buffer[64] = {c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};

	bytes = 0;
	while (length >= 64)
	{
		bytes += write(fd, buffer, 64);
		length -= 64;
	}
	bytes += write(fd, buffer, length);
	return (bytes);
}

ssize_t	ft_putbits(const uint8_t byte, int fd)
{
	uint64_t	expand;

	expand = (((uint64_t)byte * 0x8040201008040201ULL) >> 7);
	expand = (expand & 0x0101010101010101ULL) | 0x3030303030303030ULL;
	return (write(fd, &expand, 8));
}

