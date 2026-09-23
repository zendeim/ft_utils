ssize_t	ft_putnchar(char c, int fd, size_t length)
{
	size_t			i;
	ssize_t			bytes;
	size_t			buffer[256 / sizeof(size_t)];

	i = 0;
	bytes = 0;
	buffer[0] = (0x0101010101010101 & UINTPTR_MAX) * (size_t) c;
	while (i < 256 / sizeof(size_t))
		buffer[i++] = buffer[0];
	while (length >= 256)
	{
		bytes += write(fd, buffer, 256);
		length -= 256;
	}
	bytes += write(fd, buffer, length);
	return (bytes);
}
