#pragma once
#include "core.hpp"

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
