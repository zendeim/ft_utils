#pragma once
#include "core.hpp"

// === Builtin Helpers ========================================
#define MEMCPY(dst, src, n)		__builtin_memcpy(dst, src, n)
#define MEMMOVE(dst, src, n)	__builtin_memmove(dst, src, n)
#define MEMSET(dst, val, n)		__builtin_memset(dst, val, n)
#define MEMCHR(src, val, n)		__builtin_memchr(src, val, n)
#define MEMCMP(s1, s2, n)		__builtin_memcmp(s1, s2, n)
#define STRLEN(str) 			__builtin_strlen(str)

#if defined(__clang__) && __clang_major__ >= 15 && __has_builtin(__builtin_memcpy_inline)
	#define MEMCPY_INLINE(dst, src, n)	__builtin_memcpy_inline(dst, src, n)
#else
	#define MEMCPY_INLINE(dst, src, n)	__builtin_memcpy(dst, src, n)
#endif

#if defined(__clang__) && __clang_major__ >= 15 && __has_builtin(__builtin_memset_inline)
	#define MEMSET_INLINE(dst, val, n)	__builtin_memset_inline(dst, val, n)
#else
	#define MEMSET_INLINE(dst, val, n)	__builtin_memset(dst, val, n)
#endif

#define LITCMP(s1, s2)		__builtin_memcmp(s1, s2, sizeof(s2) - 1)
#define LITCPY(dst, src)	__builtin_memcpy(dst, src, sizeof(src) - 1)

// === Bit Helpers =========================================
// TODO: Get ranged versions, like start, end
#define BITREAD(word, index)	(((word) >> (index)) & 1)
#define BITSET(word, index)		((word) |= ((__typeof__(word))1 << (index)))
#define BITFLIP(word, index)	((word) ^= ((__typeof__(word))1 << (index)))
#define BITCLR(word, index)		((word) &= ~((__typeof__(word))1 << (index)))

#define CLZ(x)			__builtin_clzll(x)
#define CTZ(x)			__builtin_ctzll(x)
#define LZCNT(x)		x == 0 ? WORD_BITS : (usize)__builtin_clzll(x)
#define TZCNT(x)		x == 0 ? WORD_BITS : (usize)__builtin_ctzll(x)
#define POPCOUNT(x)		__builtin_popcountll(x)
#define PARITY(x)		__builtin_parityll(x)
#define BSWAP16(x)		__builtin_bswap16(x)
#define BSWAP32(x)		__builtin_bswap32(x)
#define BSWAP64(x)		__builtin_bswap64(x)
#define BITREVERSE(x)	__builtin_bitreverse64(x)	// This is clang specific

#define ROTL(value, shift) ({ \
	__auto_type _v = (value); \
	usize _s = (shift) & 63; \
	(_v << _s) | (_v >> ((-_s) & 63)); \
})

#define ROTR(value, shift) ({ \
	__auto_type _v = (value); \
	usize _s = (shift) & 63; \
	(_v >> _s) | (_v << ((-_s) & 63)); \
})

// === MACRO Helpers ========================================
#define JOIN_MACROS_(a, b) a##b
#define JOIN_MACROS(a, b) JOIN_MACROS_(a, b)
#define STRINGIFY_(x)		#x
#define STRINGIFY(x)		STRINGIFY_(x)

// === Generic Helpers ========================================
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

// === ASCII Helpers =======================================
#define IS_ASCII(c)	((c) >= 0 && (c) < 128)
#define IS_DIGIT(c)	((unsigned)((c) - '0') <= 9u)
#define IS_UPPER(c)	((unsigned)((c) - 'A') <= 25u)
#define IS_LOWER(c)	((unsigned)((c) - 'a') <= 25u)
#define IS_ALPHA(c) ((unsigned)(((c) | 32) - 'a') <= 25u)
#define IS_SPACE(c)	(((c) == ' ') || ((unsigned)(c) - (unsigned)'\t' <= 4u))
#define IS_HEX(c)	(IS_DIGIT(c) || (unsigned)(((c) | 32) - 'a') <= 5u)
#define IS_ALNUM(c)	(IS_DIGIT(c) || IS_ALPHA(c))
#define IS_CTRL(c)	((unsigned)(c) < 32u || (c) == 127)
#define IS_PRINT(c)	((unsigned)((c) - 32) < 95u)
