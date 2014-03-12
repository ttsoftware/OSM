
#include "tests/lib.h"
#include "proc/syscall.h"

int main(void) {

	char file[] = "[arkimedes]hej";
	int handle = syscall_open((char const*) &file);	

	char buffer[128];
	char buffer2[128];

	syscall_read(handle, &buffer, 4);
	syscall_write(handle, &buffer, 4);

	syscall_seek(handle, 0);
	syscall_read(handle, &buffer2, 11);
	syscall_write(FILEHANDLE_STDOUT, &buffer2, 11);

	syscall_close(handle);
	syscall_delete((char const*) &file);

	char file2[] = "[arkimedes]rasputin";
	syscall_create((char const*) &file2, 11);

	char buffer3[] = "\ngorbatjov\n";
	handle = syscall_open((char const*) &file2);	
	
	syscall_write(handle, &buffer3, 11);
	syscall_seek(handle, 0);
	syscall_read(handle, &buffer3, 11);
	syscall_write(FILEHANDLE_STDOUT, &buffer3, 11);	

	syscall_close(handle);

	return 0;
}