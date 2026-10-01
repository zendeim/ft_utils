#pragma once
#include "core.hpp"

void* qmemchr_sent(void* vptr, u8 c, usize length) {
	u8* str = (u8*)vptr;
	u8* end = str + length;
	u8 tmp = *end;
	*end = c;

	const u8x64 needle = (u8x64){0} + c;

	while (true) {
		u8x64 block = *(const u8x64*)str;
		u8x64 eq = block == needle;
		u1x512 mask_ = __builtin_convertvector(eq, u1x512);
		u64 mask = BITCAST(u64, mask_);
		usize matchIndex = TZCNT(mask);
		if (matchIndex != 64) {
			str += matchIndex;
			break;
		}
		str += 64;
	}
	*end = tmp;
	return str >= end ? NULL : str;
}

ATTR(static_inl)
void* qmemchr(void* vptr, u8 c, usize length) {
	u8* str = (u8*)vptr;
	u8* end = str + length;
	const u8x64 needle = (u8x64){0} + c;
	do {
		u8x64 block;
		MEMCPY_INLINE(&block, str, 64);
		u8x64 eq = block == needle;
		u64 mask = BITCAST(u64, __builtin_convertvector(eq, bool __attribute__((ext_vector_type(64)))));
		if (mask) {
			void* result = (void*)(str + TZCNT(mask));
			return result < end ? result : NULL;
		}
		str += 64 - ((uptr)str & 63);
	} while (str < end);
	return NULL;
}

ATTR(static_inl)
void* q16memchr_b(void* vptr, u8 c, usize length) {
	u8* str = (u8*)vptr;
	u8* end = str + length;
	const u8x16 needle = (u8x16){0} + c;
	do {
		u8x16 block;
		MEMCPY_INLINE(&block, str, 16);
		u8x16 eq = block == needle;
		u16 mask = BITCAST(u16, __builtin_convertvector(eq, bool __attribute__((ext_vector_type(sizeof(needle))))));
		if (mask) {
			void* result = (void*)(str + TZCNT(mask));
			return result < end ? result : NULL;
		}
		str += 16;
	} while (str < end);
	return NULL;
}

ATTR(static_inl)
void* q32memchr_b(void* vptr, u8 c, usize length) {
	u8* str = (u8*)vptr;
	u8* end = str + length;
	const u8x32 needle = (u8x32){0} + c;
	do {
		u8x32 block;
		MEMCPY_INLINE(&block, str, 32);
		u8x32 eq = block == needle;
		u32 mask = BITCAST(u32, __builtin_convertvector(eq, bool __attribute__((ext_vector_type(sizeof(needle))))));
		if (mask) {
			void* result = (void*)(str + TZCNT(mask));
			return result < end ? result : NULL;
		}
		str += 32;
	} while (str < end);
	return NULL;
}

ATTR(static_inl)
void* q64memchr_b(const void* vptr, u8 c, usize length) {
	u8* str = (u8*)vptr;
	u8* end = str + length;
	const u8x64 needle = (u8x64){0} + c;
	do {
		u8x64 block;
		MEMCPY_INLINE(&block, str, 64);
		u8x64 eq = block == needle;
		u64 mask = BITCAST(u64, __builtin_convertvector(eq, bool __attribute__((ext_vector_type(64)))));
		if (mask) {
			void* result = (void*)(str + TZCNT(mask));
			return result < end ? result : NULL;
		}
		str += 64;
	} while (str < end);
	return NULL;
}

/*	Consider this strategy:
	First, a 64 byte load is done regardless of straddling; 
	Most strings are under this size, so the majority of cases will happen here

	Second, if needle is not present inside this 64 byte sequence:
	a) align to the next 64 byte address (some bytes may be repeat scans, doesn't matter)
	b) scan while str < end (rawmemchr would be while true)
*/

