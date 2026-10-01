#pragma once
#include <cstddef>
#include <stdint.h>

#include "core_portability.inl"
#include "core_info.inl"

typedef char				i8;
typedef unsigned char		u8;
typedef int16_t				i16;
typedef uint16_t			u16;
typedef int32_t				i32;
typedef uint32_t			u32;
typedef int64_t				i64;
typedef uint64_t			u64;
typedef __int128			i128;
typedef unsigned __int128	u128;
typedef _Float16			f16;
typedef float				f32;
typedef double				f64;
typedef size_t				usize;
typedef ptrdiff_t			isize;
typedef intptr_t			iptr;
typedef uintptr_t			uptr;
typedef unsigned char		uchar;	// For completeness, to mirror platform's type
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

// typedef u8 xmm __attribute__((vector_size(16)));
// typedef u8 ymm __attribute__((vector_size(32)));
// typedef u8 zmm __attribute__((vector_size(64)));
// typedef u8 wmm __attribute__((vector_size(MAX_VECTOR_BYTES)));	// Widest register available

// Clang Specific
typedef bool u1x __attribute__((ext_vector_type(MAX_VECTOR_BYTES)));
typedef bool u1x8 __attribute__((ext_vector_type(1)));
typedef bool u1x16 __attribute__((ext_vector_type(2)));
typedef bool u1x32 __attribute__((ext_vector_type(4)));
typedef bool u1x64 __attribute__((ext_vector_type(8)));
typedef bool u1x128 __attribute__((ext_vector_type(16)));
typedef bool u1x256 __attribute__((ext_vector_type(32)));
typedef bool u1x512 __attribute__((ext_vector_type(64)));

typedef u8 u8x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef u16 u16x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef u32 u32x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef u64 u64x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef f16 f16x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef f32 f32x __attribute__((vector_size(MAX_VECTOR_BYTES)));
typedef f64 f64x __attribute__((vector_size(MAX_VECTOR_BYTES)));

static_assert(MAX_VECTOR_BITS % CHAR_BIT == 0, "Invalid vector size");
static_assert((MAX_VECTOR_BITS % 64) == 0, "Invalid vector size");

typedef u8 u8x2   __attribute__((vector_size(2)));
typedef u8 u8x4   __attribute__((vector_size(4)));
typedef u8 u8x8   __attribute__((vector_size(8)));
typedef u8 u8x16  __attribute__((vector_size(16)));
typedef u8 u8x32  __attribute__((vector_size(32)));
typedef u8 u8x64  __attribute__((vector_size(64)));

typedef u8 u8x2   __attribute__((vector_size(2)));
typedef u8 u8x4   __attribute__((vector_size(4)));
typedef u8 u8x8   __attribute__((vector_size(8)));
typedef u8 u8x16  __attribute__((vector_size(16)));
typedef u8 u8x32  __attribute__((vector_size(32)));
typedef u8 u8x64  __attribute__((vector_size(64)));

typedef u16 u16x2  __attribute__((vector_size(4)));
typedef u16 u16x4  __attribute__((vector_size(8)));
typedef u16 u16x8  __attribute__((vector_size(16)));
typedef u16 u16x16 __attribute__((vector_size(32)));
typedef u16 u16x32 __attribute__((vector_size(64)));

typedef u32 u32x2  __attribute__((vector_size(8)));
typedef u32 u32x4  __attribute__((vector_size(16)));
typedef u32 u32x8  __attribute__((vector_size(32)));
typedef u32 u32x16 __attribute__((vector_size(64)));

typedef u64 u64x2  __attribute__((vector_size(16)));
typedef u64 u64x4  __attribute__((vector_size(32)));
typedef u64 u64x8  __attribute__((vector_size(64)));

typedef f16 f16x2  __attribute__((vector_size(4)));
typedef f16 f16x4  __attribute__((vector_size(8)));
typedef f16 f16x8  __attribute__((vector_size(16)));
typedef f16 f16x16 __attribute__((vector_size(32)));
typedef f16 f16x32 __attribute__((vector_size(64)));

typedef f32 f32x2  __attribute__((vector_size(8)));
typedef f32 f32x4  __attribute__((vector_size(16)));
typedef f32 f32x8  __attribute__((vector_size(32)));
typedef f32 f32x16 __attribute__((vector_size(64)));

typedef f64 f64x2  __attribute__((vector_size(16)));
typedef f64 f64x4  __attribute__((vector_size(32)));
typedef f64 f64x8  __attribute__((vector_size(64)));
