#include <cpuid.h>
#include <ctime>
#include <x86intrin.h>
#include <unistd.h>
#include <iostream>

#include "core.hpp"
#include "HWTimer.hpp"
#include "Random.hpp"
#include "Xoroshiro128_simd.hpp"
#include "pure_functions.hpp"

// Permute function (could operate on indexes)

// Generate random indexes
// Concept of swapping memory around (shadow memory concept)

void create_random_batch(u8* buffer) {
	u64 value[8] = {16, 32, 64, 128, 512, 1024, 4096, 8192};
	u64 weights[8] = {64, 32, 16, 16, 8, 8, 8, 1};


}

template <typename Type>
void shuffle16(Type* data, u16 length) {
	for (; length > 17; length--) {
		u16x16 randomValues = (u16x16) Xoroshiro128::next4();
		const u8 targetLength = length - 16;
		for (; length > targetLength; length--) {
			usize swapIndex = (u16)(((u32)randomValues[length] * length) >> 16);
			SWAP(data[swapIndex], data[length]);
		}
	}

	u16x16 randomValues = (u16x16) Xoroshiro128::next4();
	for (; length > 1; length--) {
		usize swapIndex = (u16)(((u32)randomValues[length] * length) >> 16);
		SWAP(data[swapIndex], data[length]);
	}
}

template <typename Type>
void shuffle(Type* data, usize length) {
	for (usize i = length; i > 1; i--) {
		usize j = (usize)(((u128)Xoroshiro128::next() * i) >> 64);
		SWAP(data[i - 1], data[j]);
	}
}

template <typename Type>
void shuffle32(Type* data, usize offset) {
	u8x32 randomValues = (u8x32)Xoroshiro128::next4();
	for (usize k = 32; k > 0; k--) {
		u8 randValue = randomValues[k - 1];
		usize swapIndex = ((u16)randValue * (offset + k)) >> 8;
		SWAP(data[swapIndex], data[offset + k - 1]);
	}
}

template <typename Type>
void shuffle32(Type* data, usize offset) {
	u64x4 randomValues = Xoroshiro128::next4();

	for (usize k = 32; k > 24; k--) {
		u8 randValue = (u8)randomValues[3];
		usize swapIndex = ((u16)randValue * (offset + k)) >> 8;
		SWAP(data[swapIndex], data[offset + k - 1]);
		randomValues[3] >>= 8;
	}
	for (usize k = 24; k > 16; k--) {
		u8 randValue = (u8)randomValues[2];
		usize swapIndex = ((u16)randValue * (offset + k)) >> 8;
		SWAP(data[swapIndex], data[offset + k - 1]);
		randomValues[2] >>= 8;
	}
	for (usize k = 16; k > 8; k--) {
		u8 randValue = (u8)randomValues[1];
		usize swapIndex = ((u16)randValue * (offset + k)) >> 8;
		SWAP(data[swapIndex], data[offset + k - 1]);
		randomValues[1] >>= 8;
	}
	for (usize k = 8; k > 0; k--) {
		u8 randValue = (u8)randomValues[0];
		usize swapIndex = ((u16)randValue * (offset + k)) >> 8;
		SWAP(data[swapIndex], data[offset + k - 1]);
		randomValues[0] >>= 8;
	}
}

template <typename Type>
void shuffle256(Type* data) {
	shuffle32(data, 224);
	shuffle32(data, 192);
	shuffle32(data, 160);
	shuffle32(data, 128);
	shuffle32(data, 96);
	shuffle32(data, 64);
	shuffle32(data, 32);
	shuffle32(data, 0);
}

static inline
u8 permute8(u8 x, u64 key) {
	x += (u8)key;
	x ^= x >> 4;
	x += x << 3;
	x ^= x >> 3;
	return x;
}

template <typename Type>
void shuffle256a(Type* data) {
	Type buffer[256];
	u64 key = Xoroshiro128::next();

	for (usize i = 0; i < 256; i++) {
		buffer[i] = data[permute8(i, key)];
	}
}

template <typename Type>
void shuffle_all(Type* data, u8 length) {
	const usize numBlocks = length / 256;
	const usize rem = length % 256;
	Type* dataEnd = data + length;

	usize i = 0;
	for (; i < numBlocks; i++) {
		shuffle_(data, 256);
		data += 256;
	}
	shuffle_(dataEnd - rem, rem);
}

void permute() {

}
