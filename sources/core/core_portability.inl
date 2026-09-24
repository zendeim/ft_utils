#pragma once

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
