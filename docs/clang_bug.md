	ATTR(static_inl, const) constexpr
	u64x splitmix64_batch(u64 seed) {
		u64x result = {};

		result[0] = splitmix64(seed);
		for (usize i = 1; i < ARRAY_SIZE(result); i++) {
			result[i] = splitmix64(result[i - 1]);
		}
		return result;
	}

	without = {}; it crashes


	PLEASE submit a bug report to https://github.com/llvm/llvm-project/issues/ and include the crash backtrace, preprocessed source, and associated run script. 
Stack dump: 
0.      Program arguments: clang++ -Isources -Isources/string -Isources/core -Isources/math -Isources/math/random -Isources/utils -Isources/simd -Isources/time -Isources/io -Isources/io/buffer -Isou
rces/test -Isources/test/logger -Wall -Wextra -O2 -std=c++23 -fno-exceptions -g -DDEBUG_MODE -O0 -Wpedantic -Wshadow -Wcast-qual -Wfloat-equal -Wswitch-default -Wconversion -Wsign-conversion -fsanit
ize=address,undefined,leak -fno-omit-frame-pointer -Wno-gnu-statement-expression-from-macro-expansion -Wno-gnu-anonymous-struct -Wno-gnu-auto-type -c sources/main.cpp -o build/obj/main.o 
1.      <eof> parser at end of file 
2.      Per-file LLVM IR generation 
3.      sources/math/random/Random.hpp:16:7: Generating code for declaration 'Random::splitmix64_batch' 
#0 0x00007f7f43f98297 llvm::sys::PrintStackTrace(llvm::raw_ostream&, int) /usr/src/debug/llvm/llvm-project-22.1.8.src/llvm/lib/Support/Unix/Signals.inc:842:22 
#1 0x00007f7f43f95c27 llvm::sys::RunSignalHandlers() /usr/src/debug/llvm/llvm-project-22.1.8.src/llvm/lib/Support/Signals.cpp:108:20 
#2 0x00007f7f43f95c27 llvm::sys::CleanupOnSignal(unsigned long) /usr/src/debug/llvm/llvm-project-22.1.8.src/llvm/lib/Support/Unix/Signals.inc:376:31 
#3 0x00007f7f43e4695f HandleCrash /usr/src/debug/llvm/llvm-project-22.1.8.src/llvm/lib/Support/CrashRecoveryContext.cpp:73:5 
#4 0x00007f7f43e4695f CrashRecoverySignalHandler /usr/src/debug/llvm/llvm-project-22.1.8.src/llvm/lib/Support/CrashRecoveryContext.cpp:390:62 
#5 0x00007f7f42e3e6f0 (/usr/lib/libc.so.6+0x3e6f0) 
#6 0x00007f7f43019ad8 (/usr/lib/libc.so.6+0x219ad8) 
clang++: error: clang frontend command failed with exit code 139 (use -v to see invocation)