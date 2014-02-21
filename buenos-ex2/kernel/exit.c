
#include "kernel/exit.h"
#include "lib/libc.h"
#include "proc/process.h"

void syscall_exit(int retval) {
	process_finish(retval);
}