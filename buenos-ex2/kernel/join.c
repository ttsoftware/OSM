
#include "kernel/join.h"
#include "lib/libc.h"
#include "proc/process.h"

int syscall_join(int pid) {

	return process_join(pid);
}