1. Figure the project structure out
	This means proper scoping of modules, how dependencies are handled, whether or not C++ is a requirement, etc
	Ideally, anything that can be pure C should be.

2. Define register sizes in info
	Something useful would be a MAX_REGISTER_SIZE for when register pressure is an issue, and when it isnt
	
3. Implement variadic macro printf
	writev (write a writev wrapper for windows)
	constexpr num length

4. https://clang.llvm.org/docs/analyzer/checkers.html read more, remember matrix
-minline-all-stringops

5. Write a module for vector intrinsics
	This would enable specialization when necessary and to isolate clang's requirement