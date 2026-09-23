// TODO: Return total bytes without separator
size_t	ft_count_words(const char *str, const char c)
{
	size_t	count;

	count = 0;
	while (*str == c && *str != 0)
		str++;
	count = (*str != 0);
	while (*str != 0)
	{
		count += (str[0] == c) && (str[1] != c) && (str[1] != 0);
		str++;
	}
	return (count);
}


size_t	ft_replace(char *str, unsigned char old_char, unsigned char new_char)
{
	size_t	count;

	count = 0;
	while (*str != 0)
	{
		if (*str == old_char)
		{
			*str = new_char;
			count++;
		}
		str++;
	}
	return (count);
}

const
char	*ft_strfind(const char *str, const char *charset, uint8_t ref)
{
	size_t	i;
	size_t	lookup_table[256 / sizeof(size_t)];

	i = 0;
	while (i < (256 / sizeof(size_t)))
		lookup_table[i++] = 0UL;
	while (*charset != 0)
	{
		((uint8_t *)lookup_table)[(uint8_t)(*charset)] = 1;
		charset++;
	}
	ref = (ref != 0);
	((uint8_t *)lookup_table)[0] = ref;
	while (((uint8_t *)lookup_table)[(uint8_t)(*str)] != ref)
		str++;
	if (*str != 0)
		return (str);
	return (NULL);
}

int32_t	ft_strwcmp(const char *str, const char *pattern)
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

// Copies a null terminated array of strings into a single buffer
// Returns: NULL on full copy, or the mutated vec array for incomplete copies
const char	**ft_strvcpy(
	char **restrict			wdst	/*mutable pointer to a buffer*/,
	const char **restrict	vec		/*null terminated array of cstrings*/,
	char *restrict			end		/*end = pointer to the end of the buffer*/)
{
	const char	*restrict	src;
	char		*restrict	dst;
	size_t					length;
	size_t					space_left;

	dst = (char *restrict)*wdst;
	while (*vec != NULL)
	{
		src = (const char *restrict)*vec++;
		length = ft_strlen(src) + (*vec == NULL);
		while (length > 0)
		{
			if (dst >= end)
				return (vec - 1);
			space_left = (size_t)(end - dst);
			if (length < space_left)
				space_left = length;
			length -= space_left;
			while (space_left-- > 0)
				*dst++ = *src++;
			*wdst = dst;
			vec[-1] = src;
		}
	}
	return (NULL);
}