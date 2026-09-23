/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:17:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/03/08 23:58:26 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_puthex(unsigned char c)
{
	char	*base;

	base = "0123456789abcdef";
	write(1, &(base[c / 16]), 1);
	write(1, &(base[c % 16]), 1);
}

void	print_address(unsigned long long addr)
{
	int		i;
	char	hex[16];
	char	*base;

	base = "0123456789abcdef";
	i = 0;
	while (i < 16)
	{
		hex[15 - i] = base[addr % 16];
		addr /= 16;
		i++;
	}
	i = 0;
	while (i < 16)
	{
		write(1, &(hex[i]), 1);
		i++;
	}
	write(1, ":", 1);
	write(1, " ", 1);
}

void	print_hex_part(unsigned char *ptr, unsigned int n, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < 16)
	{
		if (n + i < size)
			ft_puthex(ptr[n + i]);
		else
		{
			write(1, " ", 1);
			write(1, " ", 1);
		}
		if (i % 2 == 1)
			write(1, " ", 1);
		i++;
	}
}

void	print_char_part(unsigned char *ptr, unsigned int n, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < 16 && n + i < size)
	{
		if (ptr[n + i] >= 32 && ptr[n + i] < 127)
			write(1, &(ptr[n + i]), 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	unsigned char	*ptr;

	ptr = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		print_address((unsigned long long)(ptr + i));
		print_hex_part(ptr, i, size);
		print_char_part(ptr, i, size);
		i += 16;
	}
	return (addr);
}

int main()
{
	char *str = "This is kind of a long test to see if this is going to work or not";
	ft_print_memory(str, 67);
}