/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:31:56 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/11 23:36:43 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

size_t	ft_strlen(const char *str);

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

// TODO
char	*ft_strnstr(const char *str, const char *substr, size_t length)
{
	size_t	i;
	size_t	str_len;
	size_t	substr_len;

	str_len = 0;
	while (str[str_len] != 0)
		str_len++;
	substr_len = 0;
	while (substr[substr_len] != 0)
		substr_len++;
	if (length > str_len)
		length = str_len;
	while (length >= substr_len)
	{
		i = 0;
		while (i < substr_len && str[i] == substr[i])
			i++;
		if (i == substr_len)
			return ((char *)str);
		str++;
		length--;
	}
	return (NULL);
}

int	ft_strwcmp(const char *str, const char *pattern)
{
	size_t			i;
	const uintptr_t	ostr = (uintptr_t) str - (*pattern == '*');

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == pattern[i])
			i++;
		else if (pattern[i] == '*')
		{
			pattern += i + 1;
			str += i;
			i = 0;
		}
		else if ((uintptr_t) str != ostr)
		{
			i = 0;
			str++;
		}
		else
			return (0);
	}
	while (pattern[i] == '*')
		i++;
	return (pattern[i] == 0);
}
