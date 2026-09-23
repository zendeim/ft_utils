#pragma once
#include "core.hpp"

// Macro Helpers
#define JOIN_MACROS_(a, b) a##b
#define JOIN_MACROS(a, b) JOIN_MACROS_(a, b)
#define STRINGIFY_(x)		#x
#define STRINGIFY(x)		STRINGIFY_(x)
#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof((arr)[0]))
#define ARRAY_END(arr)		(&(arr)[ARRAY_SIZE(arr)])

#define SWAP(a, b)			({__typeof__(a) _swap_tmp_ = (a); (a) = (b); (b) = _swap_tmp_; (void)0;})
#define ALIGN_UP(x, a)		(((x) + ((a) - 1)) & ~((a) - 1))
#define ALIGN_DOWN(x, a)	((x) & ~((a) - 1))
#define IS_POW2(x)			((x) != 0 && ((x) & ((x) - 1)) == 0)
#define NEXT_POW2(x)		((__typeof__(x))((usize)1 << ((sizeof(x) * 8) - (usize)CLZ(x))))

// === MINMAX Helpers ========================================
#define MIN(x, y)			((x) < (y) ? (x) : (y))
#define MAX(x, y)			((x) > (y) ? (x) : (y))
#define ABS(x)				((x) > 0 ? (x) : -(x))
#define CLAMP(x, low, high)	MAX(low, MIN(x, high))

#define ABSMAX(x, y)		MAX(ABS(x), ABS(y))
#define ABSMIN(x, y)		MIN(ABS(x), ABS(y))
#define ABSDIFF(x, y)		(MAX(x, y) - MIN(x, y))

#define MIN3(x, y, z)		MIN(x, MIN(y, z))
#define MAX3(x, y, z)		MAX(x, MAX(y, z))
#define MIN4(x, y, z, w)	MIN(MIN(x, y), MIN(z, w))
#define MAX4(x, y, z, w)	MAX(MAX(x, y), MAX(z, w))

#define ABSMIN3(x, y, z)	MIN3(ABS(x), ABS(y), ABS(z))
#define ABSMAX3(x, y, z)	MAX3(ABS(x), ABS(y), ABS(z))
#define ABSMIN4(x, y, z, w)	MIN4(ABS(x), ABS(y), ABS(z), ABS(w))
#define ABSMAX4(x, y, z, w)	MAX4(ABS(x), ABS(y), ABS(z), ABS(w))
