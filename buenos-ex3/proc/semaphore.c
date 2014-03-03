#include "proc/semaphore.h"
#include "proc/syscall.h"
#include "kernel/semaphore.h"
#include "lib/libc.h"
#include "kernel/assert.h"
#include "kernel/interrupt.h"
#include "kernel/sleepq.h"

#define MAX_SEMAPHORES 128

/* Array to hold userland semaphores, same length as kernel semaphore
 * array. */
static usr_sem_t usr_sem_table[MAX_SEMAPHORES];

/* Spinlock to avoid synchronization problems in destroy. */
static spinlock_t usr_sem_table_slock;

/* Initiliazing the userland semaphore array. */
void usr_sem_init(void){
    int i;
    
    spinlock_reset(&usr_sem_table_slock);
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        usr_sem_table[i].SId = -1;
    }
}

/* Opens the semaphore, it makes sure, that the name size is valid and
 * that there is room in the semaphore table. */
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

/* Procures the userland semaphore, if it exists. */
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

/* Vacates the userland semaphore, if it exists. */
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

/* Destroys the userland semaphore and makes new room in the table. */
int syscall_sem_destroy(usr_sem_t* handle) {
    int i;

    interrupt_status_t intr_status;

    intr_status = _interrupt_disable();
    spinlock_acquire(&handle->slock);
    
    semaphore_destroy(handle->kernel_sem);
    for(i = 0; i < MAX_SEMAPHORES; i++) {
        if(stringcmp(handle->sem_name,usr_sem_table[i].sem_name) == 0) {
            usr_sem_table[i].SId = -1;        
        }
    }
    
    spinlock_release(&handle->slock);
    _interrupt_set_state(intr_status);
    return 0;
}

