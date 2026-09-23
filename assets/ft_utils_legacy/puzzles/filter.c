/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:25:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/03 13:05:23 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// realloc, free, printf, fprintf, stdout, stderr, perror

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	size_t	length;
	char	*str = NULL;
	char 	*ptr;
	ssize_t	bytes_read = 0;

	length = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		ptr = realloc(str, length + (size_t)bytes_read);
		if (ptr == NULL)
		{
			perror("Error: ");
			free(str);
			return (NULL);
		}
		str = ptr;
		memmove(str + length, buffer, (size_t) bytes_read);
		length += (size_t) bytes_read;
		if (str[length - 1] == '\n')
			return (str);
	}
	if (bytes_read == -1)
	{
		perror("Error: ");
		free(str);
		return (NULL);
	}
	return (str);
}

void	replace(char *ptr, size_t length)
{
	while (length > 0)
	{
		*ptr++ = '*';
		length--;
	}
}

int	ft_filter(char *str, char *pat, size_t pat_len)
{
	const size_t	str_len = strlen(str);
	char			*ptr;

	while ((ptr = memmem(str, str_len, pat, pat_len)) != NULL)
		replace(ptr, pat_len);
	if (write(STDOUT_FILENO, str, str_len) == -1)
	{
		free(str);
		perror("Error: ");
		return (1);
	}
	free(str);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*pat;
	size_t	pat_len;
	char	*line;

	if (argc != 2 || (argc == 2 && argv[1] == NULL) || (argc == 2 && *argv[1] == 0))
		return (1);
	pat = argv[1];
	pat_len = strlen(pat);
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (ft_filter(line, pat, pat_len) == 1)
			return (1);
	}
	return (0);
}
