#ifndef BUENOS_PROC_SEMAPHORE
#define BUENOS_PROC_SEMAPHORE

#include "lib/types.h"

typedef struct {
    char const* name;
    int value;
} usr_sem_t;

usr_sem_t* syscall_sem_open(char const* name, int value);

int syscall_sem_p(usr_sem_t* handle);

int syscall_sem_v(usr_sem_t* handle);

int syscall_sem_destroy(usr_sem_t* handle);

#endif
