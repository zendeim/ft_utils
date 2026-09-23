/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:35 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/09 12:26:49 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
	size_t	num_open;
	size_t	num_close;
	ssize_t	pdepth;
	size_t	open[64];
	size_t	close[64];
}	t_par;

// (()(()(
bool	next_comb(size_t *comb, size_t comb_size, size_t max_size)
{
	size_t	i = comb_size - 1;

	while (comb[i] + 1 >= max_size - (comb_size - i))
	{
		if (i == 0)
			return (false);
		i--;
	}
	comb[i] += 1;
	i++;
	while (i < comb_size)
	{
		comb[i] = comb[i - 1] + 1;
		i++;
	}
	return (true);
}

void	str_copy(char *dst, const char *src, size_t length)
{
	while (length > 0)
	{
		*dst++ = *src++;
		length--;
	}
	*dst++ = '\n';
	*dst = 0;
}

bool	is_valid(const char *str)
{
	ssize_t	pdepth = 0;
	char	c;

	while (*str != 0)
	{
		c = *str;
		pdepth += (c == '(') - (c == ')');
		if (pdepth < 0)
			return (false);
		str++;
	}
	return (pdepth == 0);
}

void	print_str(size_t *offset_array, size_t *seq, const char *str, size_t length, size_t comb_size)
{
	char	str_buffer[4096];
	size_t	offset;
	size_t	i = 0;

	str_copy(str_buffer, str, length);
	while (i < comb_size)
	{
		offset = offset_array[seq[i]];
		str_buffer[offset] = ' ';
		i++;
	}
	if (is_valid(str_buffer))
		write(1, str_buffer, length + 1);
}

void	get_valid(size_t *offset_array, const char *str, size_t length, size_t comb_size, size_t max_size)
{
	size_t	i;
	size_t	seq[64];

	for (i = 0; i < 64; i++)
		seq[i] = i;
	print_str(offset_array, seq, str, length, comb_size);
	while (next_comb(seq, comb_size, max_size))
		print_str(offset_array, seq, str, length, comb_size);
}

int	main(int argc, char **argv, char **envp)
{
	static t_par	par;
	char 	c;
	char	*str = "(()(()(";
	char	*ostr = str;
	size_t 	length = strlen(str);

	while (*str != 0)
	{
		c = *str;
		if (c == '(')
		{
			par.open[par.num_open] = (size_t)(str - ostr);
			par.num_open++;
			par.pdepth++;
		}
		else if (c == ')')
		{
			par.close[par.num_close] = (size_t)(str - ostr);
			par.num_close++;
			par.pdepth--;
		}
		str++;
	}
	if (par.pdepth > 0)
	{
		get_valid(par.open, ostr, length, (size_t)par.pdepth, par.num_open);
	}
	else if (par.pdepth < 0)
	{
		get_valid(par.close, ostr, length, (size_t) (-par.pdepth), par.num_close);
	}
	return (0);
}
