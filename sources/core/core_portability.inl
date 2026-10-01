#pragma once
#include <cstddef>
#include <stdint.h>
#include <climits>
/*
	This supports Windows and Linux, and x86-64 and ARM

	For now, 32 bit is out of scope, but ideally it should be able to
	support any architecture

	TODO: 
		1) Figure out how to do runtime detection
			* Runtime detection might not be ideal. It might be better to compile multiple binaries instead
		2) Some of the defines are linux specific
*/

#define WORD_SIZE	sizeof(size_t)
#define WORD_BITS	(WORD_SIZE * CHAR_BIT)
#define PAGE_SIZE	4096ul
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

#if defined(_WIN32)
	#include <io.h>
	#define STDIN_FD 0
	#define STDOUT_FD 1
	#define STDERR_FD 2
	#define READ(fd, buf, len) _read((fd), (buf), (unsigned int)(len))
	#define WRITE(fd, buf, len) _write((fd), (buf), (unsigned int)(len))
#else
	#include <unistd.h>
	#define STDIN_FD STDIN_FILENO
	#define STDOUT_FD STDOUT_FILENO
	#define STDERR_FD STDERR_FILENO
	#define READ(fd, buf, len) read((fd), (buf), (len))
	#define WRITE(fd, buf, len) write((fd), (buf), (len))
#endif

#if defined(__x86_64__)
	#include <x86intrin.h>
	#include <cpuid.h>

	#if defined(__AVX512F__) 
		#define ARCH_X86 4
	#elif defined(__AVX2__)
		#define ARCH_X86 3
	#elif defined(__SSE4_2__)
		#define ARCH_X86 2
	#else
		#define ARCH_X86 1
	#endif

	#if defined(__AVX512F__)
		#define MAX_VECTOR_BITS 512
	#elif defined(__AVX2__) || defined(__AVX__)
		#define MAX_VECTOR_BITS 256
	#endif

#elif defined(__aarch64__)
	#include <arm_neon.h>

	#if defined(__ARM_FEATURE_SVE)
		#include <arm_sve.h>
		#define ARCH_ARM 1
		#define MAX_VECTOR_BITS 512
		#if defined(__ARM_FEATURE_SVE_BITS) && __ARM_FEATURE_SVE_BITS
			#define MAX_ARM_VECTOR_BITS __ARM_FEATURE_SVE_BITS
		#endif
	#else
		#define ARCH_ARM 0
	#endif

#else
	#error Unsupported architecture
#endif

#ifndef MAX_VECTOR_BITS
	#define MAX_VECTOR_BITS 128
#endif

#define MAX_VECTOR_BYTES (MAX_VECTOR_BITS / CHAR_BIT)
