#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "stack.h"

int main(void) {

	struct stack_t *stack = (struct stack_t *) malloc (sizeof (struct stack_t));
    
    stack_init(stack);

/*
    pthread_t* worker_1;
    pthread_t* worker_2;

    pthread_create(worker_1, NULL);
    pthread_create(worker_2, NULL);
*/
    // Hvorfor skal vores testprogram være så fucking kompliceret?
}