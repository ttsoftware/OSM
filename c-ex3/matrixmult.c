#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "stack.h"

int main(void) {

	struct stack_ty *stack = (struct stack_ty *) malloc (sizeof (struct stack_ty));
    
    stack_init(stack); 

/*
    pthread_t* worker_1;
    pthread_t* worker_2;

    pthread_create(worker_1, NULL);
    pthread_create(worker_2, NULL);
    */
}
