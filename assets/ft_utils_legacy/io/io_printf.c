/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:04:04 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/02 10:02:03 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>

static
ssize_t	print_nbr(uint64_t number, const char f, const char *base)
{
	char				buffer[32];
	const uint_fast8_t	radix = 10 + 6 * (f == 'x' || f == 'X' || f == 'p');
	const uint_fast8_t	sign = (f == 'd' || f == 'i') && (int32_t) number < 0;
	char				*ptr;

	if (f == 'p' && number == 0)
		return (write(1, "(nil)", 5));
	ptr = buffer + 31;
	if (sign != 0)
		number = (uint32_t)(-(int64_t)number);
	*ptr = base[(number % radix)];
	number /= radix;
	while (number != 0)
	{
		*(--ptr) = base[(number % radix)];
		number /= radix;
	}
	if (sign != 0)
		*(--ptr) = '-';
	else if (f == 'p')
	{
		*(--ptr) = 'x';
		*(--ptr) = '0';
	}
	return (write(1, ptr, (size_t)(32 - (ptr - buffer))));
}

static
ssize_t	print_str(const char *str)
{
	const char	*ostr = str;

	if (str == NULL)
		return (write(1, "(null)", 6));
	while (*str != 0)
		str++;
	return (write(1, ostr, str - ostr));
}

static
ssize_t	parse(const char f, va_list *args)
{
	static const char	base_tbl[2][16] = {{'0', '1', '2', '3', '4', '5', '6',
		'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}, {'0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}};
	char				c;

	if (f == 's')
		return (print_str((char *) va_arg(*args, char *)));
	if (f == 'p')
		return (print_nbr(va_arg(*args, uintptr_t), f, base_tbl[f == 'X']));
	if (f == 'd' || f == 'i' || f == 'u' || f == 'x' || f == 'X')
		return (print_nbr(va_arg(*args, unsigned int), f, base_tbl[f == 'X']));
	if (f == 'c')
	{
		c = (char) va_arg(*args, unsigned int);
		return (write(1, &c, 1));
	}
	return (0);
}

ssize_t	ft_printf(const char *str, ...)
{
	ssize_t		bytes;
	va_list		args;
	const char	*ostr;

	bytes = 0;
	va_start(args, str);
	while (*str != 0)
	{
		ostr = str;
		while (*str != '%' && *str != 0)
			str++;
		bytes += write(1, ostr, str - ostr + (str[0] == '%' && str[1] == '%'));
		if (*str == '%' && *(str + 1) == '%')
			str++;
		else if (*str == '%')
			bytes += parse(*++str, &args);
		str += (*str != 0);
	}
	va_end(args);
	return (bytes);
}

// #include <limits.h>
// #include <stdio.h>

// int main()
// {
// 	ft_printf("ab%%cd%d", 50);
// 	printf("\n");
// 	// printf test;
// }