#ifndef BUENOS_PROC_SEMAPHORE
#define BUENOS_PROC_SEMAPHORE

#include "lib/types.h"
#include "kernel/spinlock.h"
#include "kernel/semaphore.h"

#define MAX_NAME_SIZE 50

/* userland semaphore stucture */
typedef struct {
    char sem_name[MAX_NAME_SIZE];
    int SId;
    semaphore_t* kernel_sem;
    spinlock_t slock;
} usr_sem_t;

/* Initiliazing the userland semaphore table */
void usr_sem_init(void);

usr_sem_t* syscall_sem_open(char const* name, int value);

int syscall_sem_p(usr_sem_t* handle);

int syscall_sem_v(usr_sem_t* handle);

int syscall_sem_destroy(usr_sem_t* handle);

#endif
