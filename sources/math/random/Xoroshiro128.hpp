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
	static_inl u64x stateLow = Random::splitmix64_batch(0xE220A8397B1DCDAFULL);
	static_inl u64x stateHigh = Random::splitmix64_batch(0xA0761D6478BD642FULL);

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
	u64x next_batch() {
		const u64x s0 = stateLow;
		u64x s1 = stateHigh;
		const u64x result = s0 + s1;

		s1 ^= s0;
		stateLow = ROTL(s0, 24) ^ s1 ^ (s1 << 16);
		stateHigh = ROTL(s1, 37);
		return result;
	}

	ATTR(static_inl)
	void random_range(u8* dst, usize length) {
		const usize bodyLength = length - length % sizeof(u64x);
		const usize tailLength = length % sizeof(u64x);

		for (usize i = 0; i < bodyLength; i += sizeof(u64x)) {
			u64x randomValues = next_batch();
			MEMCPY_INLINE(dst + i, &randomValues, sizeof(u64x));
		}

		if (tailLength) {
			u64x randomValues = next_batch();
			u8* ptr = (u8*) &randomValues;
			dst += bodyLength;
			for (usize i = 0; i < tailLength; i++)
				dst[i] = ptr[i];
		}
	}

	ATTR(static_inl)
	void random_range(u8* dst, usize length, u8 mask) {
		const u64 vecMask = (u64)mask * 0x0101010101010101ull;
		const usize bodyLength = length - length % sizeof(u64x);
		const usize tailLength = length % sizeof(u64x);

		for (usize i = 0; i < bodyLength; i += sizeof(u64x)) {
			u64x randomValues = next_batch() & vecMask;
			MEMCPY_INLINE(dst + i, &randomValues, sizeof(u64x));
		}

		if (tailLength) {
			u64x randomValues = next_batch();
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
