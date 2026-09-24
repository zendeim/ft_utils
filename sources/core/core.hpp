#pragma once
#include <cstddef>
#include <stdint.h>
#include "core_info.inl"
#include "core_types.inl"
#include "core_portability.inl"
#include "core_macros.inl"

// New Keywords
#define restrict			__restrict__
#define static_inl			static inline
#define offsetof(t, d)		__builtin_offsetof(t, d)

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
	#define static_assert(expr) _Static_assert((expr), #expr)
#elif defined(__cplusplus) && __cplusplus < 201103L
	#define static_assert(expr) typedef char JOIN_MACROS(static_assert_failed_, __LINE__)[(expr) ? 1 : -1]
#endif

#define ATTR(kind, ...) ATTR_##kind __attribute__((__VA_ARGS__))
#define ATTR_default	// No inline or static specifier
#define ATTR_noinl __attribute__((noinline))
#define ATTR_inl inline __attribute__((always_inline))
#define ATTR_static static
#define ATTR_static_inl static inline __attribute__((always_inline))

// always_inline, noinline, packed, aligned(n), cold, hot
// const: Function depends only on its arguments (doesn't read from memory)
// pure: Function produces no observable side effects (may read from memory)
// flatten: Function calls inside this function are aggressively inlined
// __attribute__((section("compressed")))

#define PRINT_LN(fd, str)		((void)!WRITE(fd, str "\n", sizeof(str)))
#define PERR_RETURN(value, str)	return (PRINT_LN(2, str), (value))
#define PERR_EXIT(value, str)	_exit((PRINT_LN(2, str), (value)))

#define UNREACHABLE()	__builtin_unreachable()
#define LIKELY(x)		__builtin_expect(!!(x), 1)
#define UNLIKELY(x)		__builtin_expect(!!(x), 0)
#define ENFORCE(x, str) (ASSERT(x, str), ASSUME(x))

#if defined(__clang__)
	#define ASSUME(x)	__builtin_assume(x)
#elif defined(__GNUC__)
	#define ASSUME(x) ((x) ? (void)0 : __builtin_unreachable())
#endif

#ifdef DEBUG_MODE
	#define ON_DEBUG(x) (x)
	#define ASSERT(x, str) ((x) != 0 ? (void)0 : (PRINT_LN(2, str), __builtin_trap()))
#else
	#define ON_DEBUG(x) ((void)0)
	#define ASSERT(x, str) ((void)0)
#endif
