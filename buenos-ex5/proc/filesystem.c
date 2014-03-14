
#include "lib/libc.h"
#include "proc/filesystem.h"
#include "drivers/gcd.h"
#include "proc/syscall.h"
#include "kernel/panic.h"
#include "kernel/assert.h"
#include "fs/vfs.h"

int syscall_open(char const* pathname) 
{
	int handle = vfs_open((char*) pathname);
	if (handle > 0) {
		return handle+2;
	}
	return -1;
}

int syscall_close(int filehandle) {
	int code = vfs_close(filehandle-2);
	if (code >= 0) {
		return code;
	}
	return -1;
}

int syscall_seek(int filehandle, int offset) {
	int code = vfs_seek(filehandle-2, offset);
	if (code >= 0) {
		return code;
	}
	return -1;
}

int syscall_create(char const* pathname, int size) {
	int code = vfs_create((char*) pathname, size);
	if (code >= 0) {
		return code;
	}
	return -1;
}

int syscall_delete(char const* pathname) {
	int code = vfs_remove((char*) pathname);
	if (code >= 0) {
		return code;
	}
	return -1;
}

int syscall_read(int filehandle, void* buffer, int length)
{
	gcd_t *gcd;
	device_t *dev;
	if (filehandle == FILEHANDLE_STDIN) {
		dev = device_get(YAMS_TYPECODE_TTY, 0);
		gcd = (gcd_t *)dev->generic_device;
		return gcd->read(gcd, buffer, length);
	} 
	else {
		int bytes_read = vfs_read(filehandle-2, buffer, length); 
		KERNEL_ASSERT(bytes_read <= length);
		return bytes_read;
	}
}

int syscall_write(int filehandle, void const* buffer, int length)
{
	gcd_t *gcd;
	device_t *dev;
	if (filehandle == FILEHANDLE_STDOUT || filehandle == FILEHANDLE_STDERR) {
		dev = device_get(YAMS_TYPECODE_TTY, 0);
		gcd = (gcd_t *)dev->generic_device;
		return gcd->write(gcd, buffer, length);
	} 
	else {
		int bytes_written = vfs_write(filehandle-2, (void*) buffer, length);
		KERNEL_ASSERT(bytes_written <= length);
		return bytes_written;
	}
}

int syscall_filecount(char const* name) {
	return vfs_filecount((char*) name);
}

int syscall_file(char const* name, int index, char* buffer) {
	return vfs_file((char*) name, index, buffer);
}