#pragma once
#include "core.hpp"
#include "HWTimer.hpp"
#include "Random.hpp"
#include "Xoroshiro128.hpp"

void create_random_batch(u8* buffer) {
	u64 value[8] = {16, 32, 64, 128, 512, 1024, 4096, 8192};
	u64 weights[8] = {64, 32, 16, 16, 8, 8, 8, 1};


}

static inline
TestRange s_create_random_range(u8* buffer) {
						// 0.3%, 3.1%, 11%, 22%, 27%, 22%, 11%, 3.1%, 0.3%
	static f32 sizes[9] = {1_MB, 32_KB, 1_KB, 64, 16, 256, 4_KB, 256_KB, 1_MB};
	static u8 bucketIndex[9] = {7, 5, 3, 1, 0, 2, 4, 6, 7};

	TestRange range = {};
	u64 randomValue = Xoroshiro128::next();
	usize pseudoGauss = (usize)POPCOUNT((u8)randomValue);
	MEMCPY_INLINE(&range, &randomValue, sizeof(u64));
	const f32x2 randomFloats = Random::random_float2(randomValue);
	const f32 sizeModifier = 0.5f + randomFloats[0];	// 0.5 ~ 1.5
	range.size = (u32)(sizeModifier * sizes[pseudoGauss]) + 1;
	range.start = CLAMP(range.start % BUFFERSIZE, 128, BUFFERSIZE - range.size - 128);
	range.value = (u8)(randomValue >> 41);
	range.ptr = buffer + range.start + (u32)(range.size * randomFloats[1]);
	range.old = *range.ptr;
	range.bucketIdx = bucketIndex[pseudoGauss];
	*range.ptr = range.value;
	return range;
}