/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:31:56 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/14 10:00:48 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

int32_t		ft_strncmp(const char *str1, const char *str2, size_t length);

size_t	ft_strlen(const char *str)
{
	const char	*ostr = str;

	while (*str != 0)
		str++;
	return ((size_t)(str - ostr));
}

const
char	*ft_strchr(const char *str, unsigned char c)
{
	if (c == 0)
	{
		while (*str != 0)
			str++;
		return (str);
	}
	while (*str != 0)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

// This needs to be tested
const
char	*ft_strrchr(const char *str, unsigned char c)
{
	const char	*end = str;

	while (*end != 0)
		end++;
	if (c == 0)
		return (end);
	while (--end >= str)
	{
		if (*end == c)
			return (end);
	}
	return (NULL);
}

const
char	*ft_strnstr(const char *str, const char *substr, size_t length)
{
	size_t	substr_len;
	size_t	str_len;

	if (*substr == 0)
		return (str);
	substr_len = ft_strlen(substr);
	str_len = ft_strlen(str);
	if (length > str_len)
		length = str_len;
	while (length >= substr_len)
	{
		if (ft_strncmp(str, substr, substr_len) == 0)
			return (str);
		str++;
		length--;
	}
	return (NULL);
}

int32_t	ft_strncmp(const char *str1, const char *str2, size_t length)
{
	while (length > 0)
	{
		if (*str1 != *str2 || *str1 == 0)
			return (*(const uint8_t *) str1 - *(const uint8_t *) str2);
		str1++;
		str2++;
		length--;
	}
	return (0);
}

