// Copies a null terminated array of strings into a single buffer
// Returns: NULL) Incomplete Copy, !NULL) pointer to the end of the copy
char	*ft_strvcpy_stt(
	char *restrict			dst	/*mutable pointer to a buffer*/,
	const char **restrict	vec	/*null terminated array of cstrings*/,
	char *restrict			end	/*end = pointer to the end of the buffer*/)
{
	static thread_local const char	*restrict	src = NULL;
	static thread_local size_t					local_index = 0;
	size_t										length;
	size_t										space_left;

	while (vec[local_index] != NULL)
	{
		if (src == NULL || *src == 0)
			src = (const char *restrict)vec[local_index];
		length = ft_strlen(src) + (vec[local_index + 1] == NULL);
		while (length > 0)
		{
			if (dst >= end)
				return (NULL);
			space_left = (size_t)(end - dst);
			if (length < space_left)
				space_left = length;
			length -= space_left;
			while (space_left-- > 0)
				*dst++ = *src++;
		}
		local_index++;
	}
	local_index = 0;
	return (dst);
}