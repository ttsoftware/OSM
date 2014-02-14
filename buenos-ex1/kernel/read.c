#include "kernel/read.h"
#include "kernel/assert.h"
#include "drivers/gcd.h"
#include "drivers/metadev.h"
#include "lib/libc.h"
#include "proc/syscall.h"

int syscall_read(int fhandle, void *buffer, int length) {

	KERNEL_ASSERT(fhandle == FILEHANDLE_STDIN);

	device_t *dev = device_get(YAMS_TYPECODE_TTY, 0);
	KERNEL_ASSERT(dev != NULL);

	gcd_t *gcd = (gcd_t *)dev->generic_device;
	KERNEL_ASSERT(gcd != NULL);

    int len = 0;
    while (len < length) {
    	gcd->read(gcd, buffer, len);
    	len++;
    }

    KERNEL_ASSERT(len == length);

	return len;
}
