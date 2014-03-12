
#include "tests/lib.h"
#include "proc/syscall.h"

int main(void) {

	char file[] = "[arkimedes]hej";
	int handle = syscall_open((char const*) &file);

	char buffer[128];

	syscall_read(handle, &buffer, 4);
	syscall_write(handle, &buffer, 4);

	syscall_seek(handle, 0);
	syscall_read(handle, &buffer, 11);
	syscall_write(FILEHANDLE_STDOUT, &buffer, 11);

	syscall_close(handle);

	char file2[] = "[arkimedes]ras-putin";
	syscall_create((char const*) &file2, 0);

	char buffer2[] = "\ngorbatjov\n";
	handle = syscall_open((char const*) &file2);	
	
	syscall_write(handle, &buffer2, 11);
	syscall_seek(handle, 0);
	syscall_read(handle, &buffer2, 11);
	syscall_write(FILEHANDLE_STDOUT, &buffer2, 11);	

	return 0;
}