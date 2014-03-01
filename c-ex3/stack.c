#include <stdlib.h>
#include <pthread.h>
#include "stack.h"
#include "dlist.h"
#include <stdio.h>

pthread_mutex_t lock;

void stack_init(stack_ty* stack) {
    pthread_mutex_init(&lock, NULL);
    stack->size = -1;
    void* data = 0;
    insert((&stack->datalist),data,0);
}

int stack_empty(stack_ty* stack) {
    return stack->size == -1;
}

void* stack_top(stack_ty* stack) {
    return stack->datalist.head;
}

/* 
 * We want to synchronize pop, so concurrent access does not yield the same data element.
 */
void* stack_pop(stack_ty* stack) {
    pthread_mutex_lock(&lock);

    if (stack->size == -1) {
        // if we encounter empty stack, we want to throw error, or wait?
        return NULL;
    }

    void* element;
    element = extract(&(stack->datalist),0);
    stack->size--;

    pthread_mutex_unlock(&lock);

    return element;
}

int stack_push(stack_ty* stack, void* data) {
    pthread_mutex_lock(&lock);

    stack->size++;
    insert((&stack->datalist),data,0);

    pthread_mutex_unlock(&lock);

    return 0;
}
