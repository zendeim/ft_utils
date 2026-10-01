#pragma once
#include "core.hpp"

// vmm 
struct vmm {
	// bool __attribute__((ext_vector_type(MAX_VECTOR_BITS))) data;
	u8 __attribute__((vector_size(MAX_VECTOR_BITS / CHAR_BIT))) data;


	// epi methods
	// movemask
	// gather
	void load_u8(u8 c) {
		data = {};
		data += c;
	}

	void cmp_and_reduce() {

	}
};

// static_assert(sizeof(vmm) == 16, "asd");