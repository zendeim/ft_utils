#pragma once
#include "core.hpp"

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
