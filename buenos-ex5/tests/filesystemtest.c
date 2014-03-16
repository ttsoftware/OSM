
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

	int ret_code = syscall_seek(handle, 12);
	printf("%d\n", ret_code);

	syscall_seek(handle, 0);
	syscall_read(handle, &buffer3, 11);
	syscall_write(FILEHANDLE_STDOUT, &buffer3, 11);	

	syscall_close(handle);

	char file3[] = "[arkimedes]putin";
	syscall_create((char const*) &file3, 11);
	handle = syscall_open((char const*) &file3);	

	char buffer4[] = "\ngorbad\n";
	syscall_write(handle, &buffer4, 11);
	
	return 0;
}