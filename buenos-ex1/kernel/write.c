#include "kernel/write.h"
#include "kernel/assert.h"
#include "drivers/gcd.h"
#include "drivers/metadev.h"
#include "lib/libc.h"
#include "proc/syscall.h"

int syscall_write(int fhandle, const void* buffer, int length) {
	if (fhandle == FILEHANDLE_STDIN) {
		device_t *dev;
		gcd_t *gcd;

		dev = device_get(YAMS_TYPECODE_TTY, 0);
		KERNEL_ASSERT(dev != NULL);

		gcd = (gcd_t *)dev->generic_device;
		KERNEL_ASSERT(gcd != NULL);

		int len = snprintf(buffer, 63, "\nHEJ.\n\n");
	    gcd->write(gcd, buffer, len);

	    len = 0;
	    while (len < length) {
	    	len += gcd->read(gcd, buffer, length);
	    }

		return len;
	}
	return 0;
}
