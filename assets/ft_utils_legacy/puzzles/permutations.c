/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:49:54 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 16:23:06 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static inline
void	set_lut(size_t *lut, size_t *perm, size_t length, size_t max_size)
{
	size_t	i;

	i = 0;
	while (i < max_size)
	{
		lut[i] = 0;
		i++;
	}
	i = 0;
	while (i < length)
	{
		lut[perm[i]] = 1;
		i++;
	}
}

static
void	overflow_fix(size_t *perm, size_t digit_pos, size_t perm_size, size_t max_size)
{
	size_t	i;
	size_t	j;
	size_t	lut[64];

	set_lut(lut, perm, digit_pos, max_size);
	i = digit_pos;
	while (i < perm_size)
	{
		j = 0;
		while (lut[j] == 1)
			j++;
		lut[j] = 1;
		perm[i] = j;
		i++;
	}
}

static
size_t	get_next_value(size_t *perm, size_t digit_pos, size_t max_size)
{
	size_t	lut[64];
	size_t	number;

	number = perm[digit_pos] + 1;
	set_lut(lut, perm, digit_pos, max_size);
	while(lut[number] == 1)
		number++;
	return (number);
}

bool	next_perm(size_t *perm, size_t perm_size, size_t max_size)
{
	size_t	i;

	i = perm_size - 1;
	perm[i] = get_next_value(perm, i, max_size);
	while (perm[i] >= max_size)
	{
		if (i == 0)
			return (false);
		i--;
		perm[i] = get_next_value(perm, i, max_size);
	}
	overflow_fix(perm, i + 1, perm_size, max_size);
	return (true);
}

size_t	ft_strlen(const char *str)
{
	const char	*ostr = str;

	while (*str != 0)
		str++;
	return ((size_t)(str - ostr));
}

void	ft_putstr(const char *str, size_t length, size_t *buffer)
{
	size_t	i;
	char	perm_str[64];

	i = 0;
	while (i < length)
	{
		perm_str[i] = str[buffer[i]];
		i++;
	}
	perm_str[i++] = '\n';
	write(1, perm_str, i);
}

char	get_min(char *str, size_t length)
{
	char	min;
	size_t	min_index = 0;
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (str[i] != 0 && str[i] < str[min_index])
			min_index = i;
		i++;
	}
	min = str[min_index];
	str[min_index] = 127;
	return (min);
}

void	ft_memcpy(char *dst, const char *src, size_t length)
{
	while (length > 0)
	{
		*dst++ = *src++;
		length--;
	}
}

void	sort_str(const char *str, size_t length, char *new_str)
{
	char	str_buffer[64];
	size_t	i;

	ft_memcpy(str_buffer, str, length + 1);
	i = 0;
	while (i < length)
	{
		new_str[i] = get_min(str_buffer, length);
		i++;
	}
	new_str[i] = 0;
}

int	main(int argc, char **argv, char **envp)
{
	const char	*str = "cab";
	size_t		buffer[64];
	size_t 		length = ft_strlen(str);
	size_t		i;
	char		sorted_str[64];

	sort_str(str, length, sorted_str);
	i = 0;
	while (i < 64)
	{
		buffer[i] = i;
		i++;
	}
	ft_putstr(sorted_str, length, buffer);
	while (next_perm(buffer, length, length))
		ft_putstr(sorted_str, length, buffer);
	return (0);
}
