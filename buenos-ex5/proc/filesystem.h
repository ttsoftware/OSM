#ifndef BUENOS_PROC_FILESYSTEM
#define BUENOS_PROC_FILESYSTEM

int syscall_open(char const* pathname);

int syscall_close(int filehandle);

int syscall_create(char const* pathname, int size);

int syscall_delete(char const* pathname);

int syscall_seek(int filehandle, int offset);

int syscall_read(int filehandle, void* buffer, int length);

int syscall_write(int filehandle, void const* buffer, int length);

#endif