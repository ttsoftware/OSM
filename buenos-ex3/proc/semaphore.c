#include "proc/semaphore.h"
#include "proc/syscall.h"
#include "kernel/semaphore.h"
#include "lib/libc.h"
#include "kernel/assert.h"

#define MAX_SEMAPHORES 128

static usr_sem_t usr_sem_table[MAX_SEMAPHORES];


void usr_sem_init(void){
    int i;
    
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        usr_sem_table[i].SId = -1;
    }
}

usr_sem_t* syscall_sem_open(char const* name, int value) {
    int i;
    
    if(strlen(name) > MAX_NAME_SIZE){
        return NULL;
    }

    if(value < 0) {
        for(i = 0; i < MAX_SEMAPHORES; i++) {
            if(stringcmp(usr_sem_table[i].sem_name,name) == 0) {
                return &(usr_sem_table[i]);
            }
        }
        return NULL;
    }
    
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        if(usr_sem_table[i].SId == -1) {
            usr_sem_table[i].kernel_sem = semaphore_create(value);
            usr_sem_table[i].SId = 0;
            stringcopy(usr_sem_table[i].sem_name,name,MAX_NAME_SIZE);
            return &(usr_sem_table[i]);
        }
    } 
    return NULL; 
}

int syscall_sem_p(usr_sem_t* handle) {
    int i;
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        if(&(usr_sem_table[i]) == handle) {
            semaphore_P(handle->kernel_sem);
            return 0;
        }
    }
    return -1;
}

int syscall_sem_v(usr_sem_t* handle) {
    int i;
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        if(&(usr_sem_table[i]) == handle) {
            semaphore_V(handle->kernel_sem);
            return 0;
        }
    }
    return -1;
}


int syscall_sem_destroy(usr_sem_t* handle) {
    int i;
    
    semaphore_destroy(handle->kernel_sem);
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        if(stringcmp(handle->sem_name,usr_sem_table[i].sem_name) == 0) {
            usr_sem_table[i].SId = -1;        
        }
    }
    return 0;
}

