/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:35:05 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/11 23:36:43 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

size_t	ft_count_words(const char *str, const char c);
void	**ft_free_array(void *array, size_t length);

char	**ft_split(const char *str, const char c)
{
	char		**str_array;
	const char	*ostr;
	size_t		count;

	count = ft_count_words(str, c);
	str_array = malloc(sizeof(char *) * (count + 1));
	if (str_array == NULL)
		return (NULL);
	count = 0;
	while (*str != 0)
	{
		while (*str == c && *str != 0)
			str++;
		ostr = str;
		while (*str != c && *str != 0)
			str++;
		if (ostr != str)
			str_array[count++] = ft_substr(ostr, 0, (size_t)(str - ostr));
		if (str_array[count - (count != 0)] == NULL)
			return ((char **) ft_free_array(str_array, count));
	}
	str_array[count] = NULL;
	return (str_array);
}

// TODO: Receive a function pointer that determines how the string is stored
// Actually no, its better to have a function that returns pointers to the start of each token
// Returns t_str *, where the caller decides what to do with each entry
// Example: Split numbers would receive atoi
char	**ft_arena_split(const char *str, const char *charset, size_t *count)
{
	char			**array;
	char			*offset;
	size_t			length;
	uint8_t			lut[256];
	const size_t	words = ft_count_tokens(str, ft_setlut256(lut, charset), &length);

	array = malloc(length + words * (sizeof(char *) + 1));
	if (array == NULL)
		return (NULL);
	offset = (char *) array + words * sizeof(char *);
	*count = 0;
	while (*str != 0)
	{
		while (*str != 0 && ft_ischarset(*str, charset) == 1)
			str++;
		length = 0;
		while (ft_ischarset(str[length], charset) == 0)
			length++;
		if (length == 0)
			break ;
		array[*count] = ft_memcpy(offset, str, length);
		array[(*count)++][length] = 0;
		offset += length + 1;
		str += length;
	}
	return (array);
}

