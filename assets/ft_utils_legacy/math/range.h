/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:59:40 by adeimlin          #+#    #+#             */
/*   Updated: 2026/05/09 00:56:44 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "core.h"

// #define NMAX(array, ...) NMAX_IMPL((array), __VA_ARGS__ __VA_OPT__(,) ARRAY_SIZE(array))

#define NMAX(array, n) \
({																\
	auto STX_array = (array);									\
	auto STX_n = (n);											\
	auto STX_max = STX_array[0];								\
	for (size_t STX_i = 1; STX_i < (size_t)STX_n; STX_i++)		\
	{															\
		if (STX_array[STX_i] > STX_max)							\
			STX_max = STX_array[STX_i];							\
	}															\
	STX_max;													\
})

#define NMIN(array, n) \
({																\
	auto STX_array = (array);									\
	auto STX_n = (n);											\
	auto STX_min = STX_array[0];								\
	for (size_t STX_i = 1; STX_i < (size_t)STX_n; STX_i++)		\
	{															\
		if (STX_array[STX_i] < STX_min)							\
			STX_min = STX_array[STX_i];							\
	}															\
	STX_min;													\
})

#define AVG(array, n)											\
({																\
	auto STX_array = (array);									\
	auto STX_n = (n);											\
	auto STX_acc = STX_array[0];								\
	for (size_t STX_i = 1; STX_i < (size_t)STX_n; STX_i++)		\
		STX_acc += STX_array[STX_i];							\
	STX_acc = STX_acc / STX_n;									\
	STX_acc;													\
})

// Function casts to double
#define HW_SQRT(number)											\
({																\
	auto STX_number_ = (number);								\
	ASSUME(STX_number_ >= 0);									\
	_Generic((STX_number_),										\
		float:       __builtin_sqrtf,							\
		long double: __builtin_sqrtl,							\
		default:     __builtin_sqrt								\
	)(STX_number_);												\
})
