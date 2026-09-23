/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:35 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/08 17:15:35 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

// (()(()(
bool	next_num(size_t *comb, size_t comb_size, size_t max_size)
{
	size_t	i;

	i = comb_size - 1;
	comb[i]++;
	while (comb[i] > max_size)
	{
		if (i == 0)
			return (false);
		comb[i - 1] += 1;
		i--;
	}
	i++;
	while (i < comb_size)
	{
		comb[i] = 0;
		i++;
	}
	return (true);
}

static
bool	check_str(const char *str, ssize_t total, size_t *mask)
{
	size_t	i;
	ssize_t	opar = 0;
	ssize_t	cpar = 0;
	ssize_t	pdepth;
	char	c;

	i = 0;
	pdepth = 0;
	while (str[i] != 0)
	{
		if (mask[i] == 0)
		{
			i++;
			continue ;
		}
		c = str[i];
		pdepth += (c == '(') - (c == ')');
		if (pdepth < 0)
			return (false);
		opar += (c == '(');
		cpar += (c == ')');
		i++;
	}
	if (pdepth == 0 && cpar == total)
		return (true);
	else
		return (false);
}

static
void	ft_print(const char *str, size_t *mask)
{
	char	str_buffer[64];
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		if (mask[i] == 0)
			str_buffer[i] = ' ';
		else
			str_buffer[i] = str[i];
		i++;
	}
	str_buffer[i++] = '\n';
	write(1, str_buffer, i);
}

static
void	get_combs(size_t total, size_t length, const char *str)
{
	size_t	mask[64];

	for (size_t i = 0; i < 64; i++)
		mask[i] = 0;
	while (true)
	{
		if (check_str(str, total, mask))
			ft_print(str, mask);
		if (next_num(mask, length, 1) == false)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	ssize_t	opar = 0;
	ssize_t	cpar = 0;
	size_t	total;
	char 	c;
	char	*str = "()())()";
	char	*ostr = str;
	size_t 	length = strlen(str);

	while (*str != 0)
	{
		c = *str;
		opar += (c == '(');
		cpar += (c == ')');
		str++;
	}
	if (cpar > opar)
		total = (size_t)opar;
	else
		total = (size_t)cpar;
	get_combs(total, length, ostr);
	return (0);
}
