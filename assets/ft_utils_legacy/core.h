#pragma once

#ifdef __cplusplus
	#include <cstddef>
	#include <cstdint>
	#include <climits>
	#define restrict __restrict__
#else
	#include <stddef.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <limits.h>
    #if __STDC_VERSION__ < 202311L
        #define auto __auto_type
		#define static_assert(cond, msg) _Static_assert(cond, msg)
    #endif
#endif

#define ALWAYS_INLINE	static inline __attribute__((always_inline))
#define NOINLINE		__attribute__((noinline))
#define PURE			__attribute__((pure))			// Function produces no observable side effects (may read from memory)
#define KPURE			__attribute__((const))			// Function depends only on its arguments (doesn't read from memory)
#define PACKED			__attribute__((packed))			// Struct has no padding
#define ALIGNED(n)		__attribute__((aligned(n)))
#define COLD			__attribute__(cold)
#define HOT				__attribute__(hot)
#define FLATTEN			__attribute__((flatten))		// Function calls inside this function are aggressively inlined

#define UNREACHABLE()	__builtin_unreachable()
#define LIKELY(x)		__builtin_expect(!!(x), 1)
#define UNLIKELY(x)		__builtin_expect(!!(x), 0)
#if defined(__clang__)
	#define ASSUME(x)	__builtin_assume(x)
#elif defined(__GNUC__)
	#define ASSUME(x) ((x) ? (void)0 : __builtin_unreachable())
#endif

#define MEMCPY_BUILTIN(dst, src, n)		__builtin_memcpy(dst, src, n)
#define MEMMOVE_BUILTIN(dst, src, n)	__builtin_memmove(dst, src, n)
#define MEMSET_BUILTIN(dst, val, n)		__builtin_memset(dst, val, n)	// TODO: memchr

#if defined(__clang__) && __has_builtin(__builtin_memcpy_inline)
	#define MEMCPY_INLINE(dst, src, n)	__builtin_memcpy_inline(dst, src, n)
#else
	#define MEMCPY_INLINE(dst, src, n)	__builtin_memcpy(dst, src, n)
#endif

#define CLZ(x)			__builtin_clzll(x)
#define CTZ(x)			__builtin_ctzll(x)
#define POPCOUNT(x)		__builtin_popcountll(x)
#define FFS(x)			__builtin_ffsll(x)
#define PARITY(x)		__builtin_parityll(x)
#define BSWAP16(x)		__builtin_bswap16(x)
#define BSWAP32(x)		__builtin_bswap32(x)
#define BSWAP64(x)		__builtin_bswap64(x)

typedef int8_t			i8;
typedef uint8_t			u8;
typedef int16_t			i16;
typedef uint16_t		u16;
typedef int32_t			i32;
typedef uint32_t		u32;
typedef int64_t			i64;
typedef uint64_t		u64;
typedef float			f32;
typedef double			f64;	// Should I include 128?
typedef size_t			usize;
typedef ptrdiff_t		isize;
typedef unsigned char	uchar;	// For completeness, to mirror platform's type
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

typedef union
{
	uint8_t u8[4]; uint16_t u16[2]; uint32_t u32;
	int8_t i8[4]; int16_t i16[2]; int32_t i32;
	float f32;
}	m32;

typedef union
{
	uint8_t u8[8]; uint16_t u16[4]; uint32_t u32[2]; uint64_t u64;
	int8_t i8[8]; int16_t i16[4]; int32_t i32[2]; int64_t i64;
	float f32; double f64;
}	m64;

#define WORD_SIZE	sizeof(size_t)
#define WORD_BITS	(WORD_SIZE * CHAR_BIT)
#define PI			3.141592653589793238462643383279502884	// TODO: get actual double representation on these
#define EULER		2.718281828459045235360287471352662497	// TODO: get actual double representation on these
#define KLOG2		0.301029995663981195213738894724493026	// TODO: this might be useless
#define DEG2RAD		(PI / 180.0)							// TODO: get actual double representation on these
#define RAD2DEG		(180.0 / PI)							// TODO: get actual double representation on these

#ifdef __cplusplus
	#define ALIGN_SIZE	alignof(std::max_align_t)
#else
	#define ALIGN_SIZE	_Alignof(max_align_t)
#endif

// === Bit Helpers =========================================
#define BIT_READ(word, index)	(((word) >> (index)) & 1)
#define BIT_SET(word, index)	((word) | ((typeof(word))1 << (index)))
#define BIT_CLR(word, index)	((word) & ~((typeof(word))1 << (index)))

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

// === Math Helpers ========================================
#define LOG2(x)				(63u - CLZ(x))	// TODO: maybe math helpers dont belong in this

// === Generic Helpers =====================================
#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof((arr)[0]))
#define ARRAY_END(arr)		(&(arr)[ARRAY_SIZE(arr)])
#define SWAP(a, b) 			({auto _swap_tmp_ = (a); (a) = (b); (b) = ___tmp; (void)0;})

#define STRINGIFY_(x)		#x
#define STRINGIFY(x)		STRINGIFY_(x)
#define ALIGN_UP(x, a)		(((x) + ((a) - 1)) & ~((a) - 1))	// TODO: rename this
#define ALIGN_DOWN(x, a)	((x) & ~((a) - 1))
#define IS_POW2(x)			(((x) & ((x) - 1)) == 0)			// UB for x==0
