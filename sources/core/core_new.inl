#pragma once
#include "core.hpp"

#ifndef __cplusplus
	#define auto __auto_type
	#define static_assert(cond, msg) _Static_assert(cond, msg)
#endif

#define BITCAST(type, value) ({ \
	auto _bitcast_src = (value); \
	static_assert(sizeof(type) == sizeof(_bitcast_src), "BITCAST size mismatch"); \
	type _bitcast_dst; \
	MEMCPY_INLINE(&_bitcast_dst, &_bitcast_src, sizeof(type)); \
	_bitcast_dst; \
})

#define SQRT(value) ({ \
	auto _sqrt_src = (value); \
	ASSUME(_sqrt_src >= 0); \
	(typeof(_sqrt_src))(__builtin_sqrt(_sqrt_src)); \
})

// Has newton raphson approximations
#define RSQRT(value) ({ \
	auto _rsqrt_src = (value); \
	ASSUME(_rsqrt_src >= 0); \
	(typeof(_rsqrt_src))1 / (typeof(_rsqrt_src))__builtin_sqrt(_rsqrt_src); \
})

// Does not
// Ideally this should be vectorizable from the same instruction
#if defined(__x86_64__)
	#define QRSQRT(x) _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
#elif defined(__aarch64__)
	#define QRSQRT(x) vrsqrtes_f32(x);
#else
	#define QRSQRT(x) RSQRT(x);
#endif
