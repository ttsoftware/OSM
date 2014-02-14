
#include "tests/lib.h"
#include "proc/syscall.h"

int main(void) {

	char buffer[64];

    int len = syscall_read(FILEHANDLE_STDIN, &buffer, 64);
	
	//kprintf((char*)&len);
	//kprintf("\n\n");

	syscall_halt();
    
    return len;
}
