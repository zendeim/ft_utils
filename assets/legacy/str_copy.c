/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:25:16 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/14 10:00:53 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <threads.h>

size_t	ft_strlen(const char *str);

char	*ft_strcpy(char *dst, const char *src)
{
	const char	*osrc = src;
	size_t		length;
	char		*odst;

	while (*src != 0)
		src++;
	length = src - osrc + 1;
	odst = dst;
	while (length > 0)
	{
		*dst++ = *osrc++;
		length--;
	}
	return (odst);
}

char	*ft_strncpy(char *dst, const char *src, size_t length)
{
	char	*odst;

	odst = dst;
	while (*src != 0 && length > 0)
	{
		*dst++ = *src++;
		length--;
	}
	while (length > 0)
	{
		*dst = 0;
		dst++;
		length--;
	}
	return (odst);
}

char	*ft_strlcpy(char *restrict dst, const char *restrict src, size_t dst_size)
{
	char		*odst;
	size_t		src_len;
	size_t		length;

	odst = dst;
	src_len = 0;
	while (src[src_len] != 0)
		src_len++;
	if (dst_size != 0)
	{
		if (dst_size > src_len)
			length = src_len;
		else
			length = dst_size - 1;
		while (length > 0)
		{
			*dst++ = *src++;
			length--;
		}
		*dst = 0;
	}
	return (odst);
}

char	*ft_strdup(const char *src)
{
	const char	*osrc = src;
	char		*str;

	while (*src != 0)
		src++;
	str = (char *) malloc((size_t)(src - osrc + 1));
	if (str == NULL)
		return (NULL);
	str += src - osrc;
	*str = 0;
	while (src > osrc)
		*--str = *--src;
	return (str);
}


