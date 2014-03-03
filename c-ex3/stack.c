#include <stdlib.h>
#include <pthread.h>
#include "stack.h"
#include "dlist.h"
#include <stdio.h>

/* Mutex lock */
pthread_mutex_t lock;
pthread_cond_t pop_cond;

/* Initialising the mutex lock, the stack size but also we insert a 0 in the stack
 * This is due to the fact, that our implementation of the Dlist does not
 * work when we only insert 2 elements and extract both of them, 
 * therefore we've made this little 'hack'. */
void stack_init(stack_ty* stack) {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&pop_cond, NULL);
    stack->size = -1;
    void* data = 0;
    insert((&stack->datalist),data,0);
}

/* Is the stack empty? */
int stack_empty(stack_ty* stack) {
    return stack->size == -1;
}

/* Top of the stack */
void* stack_top(stack_ty* stack) {
    
    return stack->datalist.head;
}

/* We want to synchronize pop, so concurrent access does not yield the same data element.
 * hence the mutex lock. We use the extract from dlist to remove elements. */
void* stack_pop(stack_ty* stack) {
    pthread_mutex_lock(&lock);

    if (stack->size == -1) {
       // pthread_cond_wait(&pop_cond,&lock); - didnt work
        return 0;
    }

    void* element;
    element = extract(&(stack->datalist),0);
    stack->size--;

    pthread_mutex_unlock(&lock);

    return element;
}

/* Synchronizing and therefore we make use of a mutex lock. */
int stack_push(stack_ty* stack, void* data) {
    pthread_mutex_lock(&lock);

    stack->size++;
    insert((&stack->datalist),data,0);

    pthread_cond_broadcast(&pop_cond);
    
    pthread_mutex_unlock(&lock);

    return 0;
}
