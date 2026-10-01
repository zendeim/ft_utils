#include <cpuid.h>
#include <ctime>
#include <x86intrin.h>
#include <unistd.h>
#include <iostream>

#include "core.hpp"
#include "HWTimer.hpp"
#include "Random.hpp"
#include "Xoroshiro128.hpp"
#include "memchr.hpp"
#include "memchr_avx.hpp"

// #include <sys/mman.h>
// u8* buffer = (u8*)mmap(nullptr, 2_GB, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// void* memchr_libc(void* vstr, u8 c, usize length) {	return MEMCHR(vstr, (int)c, length); }

// TODO: Create a shuffle, randperm function, a create weighted batch function

ATTR(noinl, flatten, aligned(64))
void* memchr_libc(void* vstr, u8 c, usize length) {	return MEMCHR(vstr, c, length); }

ATTR(noinl, flatten, aligned(64))
void* memchr_qlib(void* vstr, u8 c, usize length) {	return q16memchr_b(vstr, c, length); }

#define BUFFERSIZE 128_MB
#define NUM_EPOCHS 8_MB

using fn_memchr = void* (*)(void*, u8, usize);
static u64 throwaway = 0;

struct TestRange {
	u32 start;
	u32 size;
	u8 value;
	u8* ptr;
	u8 old;
	u8 bucketIdx;
};

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

ATTR(noinl, aligned(64))
void s_test_function(u8* buffer, u128* time, fn_memchr fnPtr) {
	TestRange range = s_create_random_range(buffer);
	u8* ptr = buffer + range.start;
	u64 t0 = HWTimer::get_tick_gated();
	void* result = fnPtr(ptr, range.value, range.size);
	u64 t1 = HWTimer::get_tick_gated();
	time[range.bucketIdx] += (t1 - t0);
	throwaway += (usize)result;
	*range.ptr = range.old;
}

int main() {
	static u8 buffer[BUFFERSIZE];
	static u128 libcTime[9] = {};
	static u128 qlibTime[9] = {};
	Xoroshiro128::random_range(buffer, sizeof(buffer), 0x7F);

	for (usize epoch = 0; epoch < NUM_EPOCHS / 2; epoch++) {
		s_test_function(buffer, qlibTime, memchr_qlib);
		s_test_function(buffer, libcTime, memchr_libc);
	}
	for (usize epoch = 0; epoch < NUM_EPOCHS / 2; epoch++) {
		s_test_function(buffer, libcTime, memchr_libc);
		s_test_function(buffer, qlibTime, memchr_qlib);
	}

	for (usize i = 0; i < 9; i++) {
		if (libcTime[i] == 0 || qlibTime[i] == 0)
			continue;
		u128 result = (qlibTime[i] << 32) / libcTime[i];
		double dblResult = (double) result / (double)(1ull << 32);
		std::cout << dblResult << ", ";
	}
	std::cout << "\n";
	return (int)throwaway % 64;
}
