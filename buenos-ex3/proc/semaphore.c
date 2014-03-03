#include "proc/semaphore.h"
#include "proc/syscall.h"
#include "kernel/semaphore.h"

#define MAX_SEMAPHORES 128

static usr_sem_t usr_sem_table[MAX_SEMAPHORES];


void usr_sem_init(void){
    int i;
    
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        usr_sem_table[i].SId = -1;
    }
}

usr_sem_t* syscall_sem_open(char const* name, int value) {    
    value = value;
    name = name;

    if(value < 0) {
    return 0;
    }
    return 0;
}

int syscall_sem_p(usr_sem_t* handle) {
    handle = handle;
    return 0;
}

int syscall_sem_v(usr_sem_t* handle) {
    handle = handle;
   /* semaphore_V((semaphore_t *) handle); */
    return 0;
}

int syscall_sem_destroy(usr_sem_t* handle) {
    handle = handle;
    return 0;
}

