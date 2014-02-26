#include <stdlib.h>
#include <pthread.h>
#include "stack.h"

pthread_mutex_t* lock;
pthread_cond_t* push_cond;

void stack_init(stack_t* stack) {
    pthread_mutex_init(lock, NULL);
    pthread_cond_init(push_cond, NULL);
    stack->size = -1;
}

int stack_empty(stack_t* stack) {
    return stack->size == -1;
}

void* stack_size(stack_t* stack) {
    return stack->data[stack->size];
}

/* 
 * We want to synchronize pop, so concurrent access does not yield the same data element.
 */
void* stack_pop(stack_t* stack) {
    pthread_mutex_lock(lock);

    if (stack->size == -1) {
        // if we encounter empty stack, we want to throw error, or wait?
        return NULL;
    }

    stack->size--;
    void* element = stack->data[stack->size];

    if (stack->size == STACK_MAX_SIZE-1) {
        // something is going to be pop'ed, so we can now signal to push
        // pthread_cond_signal(push_cond);
        pthread_cond_broadcast(push_cond); 
    }

    pthread_mutex_unlock(lock);

    return element;
}

int stack_push(stack_t* stack, void* data) {
    pthread_mutex_lock(lock);

    if (stack->size == STACK_MAX_SIZE-1) {
        // if we encounter a full stack, we want to wait.
        pthread_cond_wait(push_cond, lock);
    } 

    stack->size++;
    stack->data[stack->size] = data;

    pthread_mutex_unlock(lock);

    return 0;
}
