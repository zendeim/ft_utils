/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:15:24 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 15:40:04 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	while (isspace((char) c))
		c = fgetc(f);
	if (c == EOF)
		return (-1);
	ungetc(c, f);
    return (0);
}

int match_char(FILE *f, char c)
{
	int	new_c;

	new_c = fgetc(f);
	if ((char) new_c == c)
		return (1);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int		c = fgetc(f);
	char	*ptr;

	if (c == EOF)
		return (0);
	ptr = (char *) va_arg(ap, char *);
	*ptr = (char) c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int		sign = -1;
	char	c;
	int		*number = (int *) va_arg(ap, int *);

	*number = 0;
	c = (char) fgetc(f);
	if (c == '-')
	{
		sign = -sign;
		c = (char) fgetc(f);
	}
	else if (c == '+')
		c = (char) fgetc(f);
	if (!(c >= '0' && c <= '9'))
		return (0);
	while (c >= '0' && c <= '9')
	{
		*number = *number * 10 - (c - '0'); 
		c = (char) fgetc(f);
	}
	*number *= sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	size_t	i;
	char	c;
	char	*ptr = (char *) va_arg(ap, char *);

	i = 0;
	c = (char) fgetc(f);
	if (c == EOF)
		return (0);
	while (c != EOF && !isspace(c) && c != 0)
	{
		ptr[i] = c;
		i++;
		c = (char) fgetc(f);
	}
	if (c == 0)
		ptr[i] = c;
    return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
