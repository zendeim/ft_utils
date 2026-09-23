#include "core.hpp"
#include "Xoroshiro128_simd.hpp"

// u8 permute8(u8 x, u64 key) {
// 	x += (u8)key;
// 	x ^= x >> 4;
// 	x += x << 3;
// 	x ^= x >> 3;
// 	return x;
// }

void permute8(u8* out) {
    const u64 key = Xoroshiro128::next();
    const usize step = (key & 255) | 1;
    const usize start = (key >> 8) & 255;

    for (usize i = 0; i < 256; i++) {
        out[i] = u8(start + i * step);
    }
}

void permute16(u16* out) {
    const u64 key = Xoroshiro128::next();
    const usize step = (key & 65535) | 1;
    const usize start = (key >> 16) & 65535;

    for (usize i = 0; i < 65536; i++) {
        out[i] = u16(start + i * step);
    }
}

// Requires unsigned usize, n > 0, and n a power of two.
void perm_pow2(usize* out, usize n) {
    const usize mask = n - 1;
    const usize step = (usize(Xoroshiro128::next()) & mask) | 1;
    const usize start = usize(Xoroshiro128::next()) & mask;

    for (usize i = 0; i < n; i++)
        out[i] = (start + i * step) & mask;
}
