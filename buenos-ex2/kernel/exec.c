
#include "kernel/exec.h"
#include "lib/libc.h"
#include "proc/process.h"

int syscall_exec(char const* filename) {

	int pid = process_spawn(filename);

	return pid;
}