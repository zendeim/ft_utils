/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_perm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:10:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/09 09:22:21 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

static inline
void	ft_swap(uint8_t *a, uint8_t *b)
{
	uint8_t tmp = *a;
	*a = *b;
	*b = tmp;
}

static
bool next_perm_ref(uint8_t *perm, uint8_t perm_size)
{
	uint8_t	i, j, k;

	i = perm_size - 1;						// 1) Find rightmost i such that perm[i - 1] < perm[i]
	while (i > 0 && perm[i - 1] >= perm[i])
		i--;
	if (i == 0)
		return (false);
	j = perm_size - 1;						// 2) Find rightmost element greater than perm[i - 1]
	while (perm[j] <= perm[i - 1])
		j--;
	ft_swap(perm + i - 1, perm + j);		// 3) Swap them
	k = perm_size - 1;						// 4) Reverse suffix [i, end)
	while (i < k)
		ft_swap(perm + i++, perm + k--);
	return (true);
}
