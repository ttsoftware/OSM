#include "kernel/halt.h"
#include "kernel/hello.h"
#include "drivers/metadev.h"
#include "lib/libc.h"
#include "fs/vfs.h"

/**
 * Hello world
 */
void hello_world(void)
{
    kprintf("Hello world\n");

    halt_kernel();
}
