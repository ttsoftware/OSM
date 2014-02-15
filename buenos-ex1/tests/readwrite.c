
#include "tests/lib.h"
#include "proc/syscall.h"

int main(void) {

	char buffer[10];

	// det er read der ikke virker. Den læser kun det sidste input.
    int len = syscall_read(FILEHANDLE_STDIN, &buffer, 10);

	len = syscall_write(FILEHANDLE_STDOUT, &buffer, len);

	char _buffer[5];
	_buffer[0] = '\n';
	_buffer[1] = 'a';
	_buffer[2] = 'b';
	_buffer[3] = 'c';
	_buffer[4] = '\n';

    len = syscall_write(FILEHANDLE_STDOUT, _buffer, 5);

	syscall_halt();
    
    return 0;
}
