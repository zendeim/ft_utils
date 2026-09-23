/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2026/04/09 19:46:06 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <threads.h>
#include <fcntl.h>
#include <errno.h>

#ifndef FT_IO_BUFSIZE
# define FT_IO_BUFSIZE 4096
#endif

const char	**ft_strvcpy(char **restrict wdst,
	const char **restrict vec, char *restrict end);

// Repeats the write until the buffer is fully consumed, and repeats
// the write when a signal interrupts it.
ssize_t	ft_write(int fd, const void *buffer, size_t length)
{
	ssize_t			bytes_written;
	size_t			bytes_remaining;
	const uint8_t	*ptr = (const uint8_t *) buffer;

	bytes_remaining = length;
	while (bytes_remaining > 0)
	{
		bytes_written = write(fd, ptr, bytes_remaining);
		if (bytes_written > 0)
		{
			bytes_remaining -= (size_t) bytes_written;
			ptr += (size_t) bytes_written;
		}
		else if (errno != EINTR || bytes_written == 0)
			return (-1);
	}
	return ((ssize_t) length);
}

// Returns -1 on OOM
ssize_t	ft_read(int fd, void *buffer, void *end, size_t read_size)
{
	ssize_t			bytes_read;
	char			*ptr;
	const ptrdiff_t	bytes_free = (char *)end - (char *)buffer;

	if (bytes_free <= 0)
		return (-1);
	ptr = (char *) buffer;
	if ((size_t) bytes_free < read_size)
		read_size = (size_t) bytes_free;
	while (true)
	{
		bytes_read = read(fd, ptr, read_size);
		if (bytes_read > 0)
		{
			read_size -= (size_t) bytes_read;
			ptr += (size_t) bytes_read;
			if (read_size == 0)
				return ((ssize_t)(ptr - (char *)buffer));
		}
		else if (bytes_read == 0)
			break ;
		else if (errno != EINTR)
			return (-1);
	}
	return ((ssize_t)(ptr - (char *)buffer));
}

ssize_t	ft_read_size(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	uint8_t		buffer[16 * 1024];
	ssize_t		bytes_read;
	ssize_t		bytes_total;

	if (fd < 0)
		return (-1);
	bytes_total = 0;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		bytes_total += bytes_read;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	if (bytes_read == 0)
		return (bytes_total);
	else
		return (-1);
}
