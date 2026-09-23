/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:55:34 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/14 09:59:15 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void	*ft_memset(void *vdst, const uint8_t byte, size_t length);
char	*ft_strdup(const char *src);

// Before substr is allocated, it is used as a temp variable to store
// the starting position of (str + start), to limit the max length
char	*ft_substr(const char *str, size_t start, size_t length)
{
	const char	*str_offset = str + start;
	char		*substr;

	if (str == NULL)
		return (NULL);
	while (*str != 0)
		str++;
	if (str_offset > str)
		return (NULL);
	if (str_offset + length > str)
		length = (size_t)(str - str_offset);
	str = str_offset + length;
	substr = (char *) malloc (length + 1);
	if (substr == NULL)
		return (NULL);
	substr += length;
	*substr = 0;
	while (length > 0)
	{
		*--substr = *--str;
		length--;
	}
	return (substr);
}

// (end - 1) to avoid segfault and to not use the null terminator as LUT index
char	*ft_strtrim(const char *str, const char *charset)
{
	char		*new_str;
	const char	*end;
	uint8_t		lookup_table[256];

	ft_memset(lookup_table, 0, 256);
	while (*charset != 0)
		lookup_table[*(const uint8_t *) charset++] = 1;
	while (lookup_table[*(const uint8_t *) str] != 0)
		str++;
	end = str;
	while (*end != 0)
		end++;
	while ((end - 1) > str && lookup_table[(uint8_t) *(end - 1)] != 0)
		end--;
	new_str = (char *) malloc((size_t)(end - str + 1));
	if (new_str == NULL)
		return (NULL);
	new_str += end - str;
	*new_str = 0;
	while (end > str)
		*--new_str = *--end;
	return (new_str);
}

