#pragma once
#include "core.hpp"
#include "Span.hpp"
#include <x86intrin.h>
#include "Random.hpp"

/*
	Uses 
	https://prng.di.unimi.it/xoroshiro128plus.c

	TODO: 
		4) Make SIMD generate x8
*/

struct Xoroshiro128 {
	#ifdef __AVX512F__
		typedef u64x8 vecType;
		static_inl u64x8 stateLow = {0xE220A8397B1DCDAFULL, 0x06C45D188009454FULL, 0x1B39896A51A8749BULL, 0x2C829ABE1F4532E1ULL,
			0x3EE5789041C98AC3ULL, 0x657EECDD3CB13D09ULL, 0x8621A03FE0BBDB7BULL, 0xB54E0F1600CC4D19ULL};
		static_inl u64x8 stateHigh = {0x6E789E6AA1B965F4ULL, 0xF88BB8A8724C81ECULL, 0x53CB9F0C747EA2EAULL, 0xC584133AC916AB3CULL,
			0xF3B8488C368CB0A6ULL, 0xC2D326E0055BDEF6ULL, 0x8E1F7555983AA92FULL, 0x84BB3F97971D80ABULL};
	#else
		typedef u64x4 vecType;
		static_inl u64x4 stateLow = {0xE220A8397B1DCDAFULL, 0x06C45D188009454FULL, 0x1B39896A51A8749BULL, 0x2C829ABE1F4532E1ULL};
		static_inl u64x4 stateHigh = {0x6E789E6AA1B965F4ULL, 0xF88BB8A8724C81ECULL, 0x53CB9F0C747EA2EAULL, 0xC584133AC916AB3CULL};
	#endif

	ATTR(static_inl)
	void seed(u64 seed = __rdtsc()) {
		for (usize i = 0; i < ARRAY_SIZE(stateLow); i++) {
			stateLow[i] = Random::splitmix64(seed);
			stateHigh[i]= Random::splitmix64(stateLow[i]);
			seed = stateHigh[i];
		}
	}

	ATTR(static_inl)
	u64 next(usize stateIndex = 0) {
		const u64 s0 = stateLow[stateIndex];
		u64 s1 = stateHigh[stateIndex];
		const u64 result = s0 + s1;

		s1 ^= s0;
		stateLow[stateIndex] = ROTL(s0, 24) ^ s1 ^ (s1 << 16);
		stateHigh[stateIndex] = ROTL(s1, 37);
		return result;
	}

	ATTR(static_inl)
	vecType vec_next() {
		const vecType s0 = stateLow;
		vecType s1 = stateHigh;
		const vecType result = s0 + s1;

		s1 ^= s0;
		stateLow = ROTL(s0, 24) ^ s1 ^ (s1 << 16);
		stateHigh = ROTL(s1, 37);
		return result;
	}

	ATTR(static_inl)
	void random_range(u8* dst, usize length) {
		const usize bodyLength = length - length % sizeof(vecType);
		const usize tailLength = length % sizeof(vecType);

		for (usize i = 0; i < bodyLength; i += sizeof(vecType)) {
			vecType randomValues = vec_next();
			MEMCPY_INLINE(dst + i, &randomValues, sizeof(vecType));
		}

		if (tailLength) {
			vecType randomValues = vec_next();
			u8* ptr = (u8*) &randomValues;
			dst += bodyLength;
			for (usize i = 0; i < tailLength; i++)
				dst[i] = ptr[i];
		}
	}

	ATTR(static_inl)
	void random_range(u8* dst, usize length, u8 mask) {
		const u64 vecMask = (u64)mask * 0x0101010101010101ull;
		const usize bodyLength = length - length % sizeof(vecType);
		const usize tailLength = length % sizeof(vecType);

		for (usize i = 0; i < bodyLength; i += sizeof(vecType)) {
			vecType randomValues = vec_next() & vecMask;
			MEMCPY_INLINE(dst + i, &randomValues, sizeof(vecType));
		}

		if (tailLength) {
			vecType randomValues = vec_next();
			u8* ptr = (u8*) &randomValues;
			dst += bodyLength;
			for (usize i = 0; i < tailLength; i++)
				dst[i] = ptr[i] & mask;
		}
	}

	ATTR(static_inl)
	void jump(usize stateIndex = 0) {
		static const u64 jumpTable[2] = {0xdf900294d8f554a5, 0x170865df4b3201fc};

		u64 s0 = 0;
		u64 s1 = 0;
		for (usize i = 0; i < 2; i++) {
			for (usize bitIndex = 0; bitIndex < 64; bitIndex++) {
				if (jumpTable[i] & 1ull << bitIndex) {
					s0 ^= stateLow[stateIndex];
					s1 ^= stateHigh[stateIndex];
				}
				next(stateIndex);
			}
		}
		stateLow[stateIndex] = s0;
		stateHigh[stateIndex] = s1;
	}
};

// u64x4 next4(u64x4& s0, u64x4& s1) {
// 	const u64x4 a = s0;
// 	u64x4 b = s1;
// 	const u64x4 result = a + b;

// 	b ^= a;
// 	s0 = vec_rotl(a, 24) ^ b ^ (b << 16);
// 	s1 = vec_rotl(b, 37);

// 	return result;
// }
