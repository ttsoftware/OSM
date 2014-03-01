#include "proc/semaphore.h"
#include "proc/syscall.h"

usr_sem_t* syscall_sem_open(char const* name, int value) {
    name = name;
    value = value;

    return 0;
}

int syscall_sem_p(usr_sem_t* handle) {
    handle = handle;
    return 0;
}

int syscall_sem_v(usr_sem_t* handle) {
    handle = handle;
    return 0;
}

int syscall_sem_destroy(usr_sem_t* handle) {
    handle = handle;
    return 0;
}

