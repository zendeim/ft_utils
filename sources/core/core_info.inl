#pragma once
#include <limits>
#include <climits>

#include "core.hpp"

/* Acts as an expansion to sizeof function:
	sizeof_bits:	number of bits of that type
	sizeof_max:		maximum size of that type
	sizeof_min:		lowest size of that type
	sizeof_array:	element count of an array
	sizeof_digits:	number of digits to represent the max size of the type
*/

#define WORD_SIZE	sizeof(size_t)
#define WORD_BITS	(WORD_SIZE * CHAR_BIT)

#define MAX_PATH_SIZE (4096ul)

#ifdef PIPE_BUF
	#if PIPE_BUF > 4096
		#define ATOMIC_IOSIZE 4096
	#else
		#define ATOMIC_IOSIZE PIPE_BUF
	#endif
#else
	#ifdef _POSIX_PIPE_BUF
		#define ATOMIC_IOSIZE _POSIX_PIPE_BUF
	#else
		#define ATOMIC_IOSIZE 512
	#endif
#endif

constexpr unsigned long long operator""_G(unsigned long long x) {
	return x * 1000000000ULL;
}

constexpr unsigned long long operator""_M(unsigned long long x) {
	return x * 1000000ULL;
}

constexpr unsigned long long operator""_K(unsigned long long x) {
	return x * 1000ULL;
}

constexpr unsigned long long operator""_GB(unsigned long long x) {
	return x * 1024ULL * 1024ULL * 1024ULL;
}

constexpr unsigned long long operator""_MB(unsigned long long x) {
	return x * 1024ULL * 1024ULL;
}

constexpr unsigned long long operator""_KB(unsigned long long x) {
	return x * 1024ULL;
}

template <typename Type>
static constexpr usize sizeof_bits(const Type&) {
	return sizeof(Type) * CHAR_BIT;
}

template <typename Type>
static constexpr Type sizeof_max(const Type&) {
	return std::numeric_limits<Type>::max();
}

template <typename Type>
static constexpr Type sizeof_min(const Type&) {
	return std::numeric_limits<Type>::lowest();
}

template <typename Type, usize Count>
static constexpr usize sizeof_array(const Type (&)[Count]) {
	return Count;
}

template <typename Type>
static constexpr usize sizeof_digits8(const Type&) {
	return (sizeof(Type) * CHAR_BIT + 2) / 3;
}

template <typename Type>
static constexpr usize sizeof_digits10(const Type&) {
	return std::numeric_limits<Type>::digits10 + 1;
}

template <typename Type>
static constexpr usize sizeof_digits16(const Type&) {
	return (sizeof(Type) * CHAR_BIT + 3) / 4;
}

template <>
constexpr f32 sizeof_min<f32>(const f32&) {
	return -std::numeric_limits<f32>::max();
}

template <>
constexpr f64 sizeof_min<f64>(const f64&) {
	return -std::numeric_limits<f64>::max();
}
