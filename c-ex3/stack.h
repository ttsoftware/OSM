#ifndef STACK_H
#define STACK_H

#define STACK_MAX_SIZE 1024

typedef struct stack_ty {
  void* data[STACK_MAX_SIZE];
  int size;
} stack_ty;

/* Initialise a freshly allocated stack.  Must be called before using
   any of the other stack functions. */
void stack_init(stack_ty*);

/* Returns true if the stack is empty. */
int stack_empty(stack_ty*);

/* Return the top element of the stack. Undefined behaviour if the
   stack is empty. */
void* stack_top(stack_ty*);

/* Remove the top element of the stack and return it. Undefined
   behaviour if the stack is empty. */
void* stack_pop(stack_ty*);

/* Push an element to the top of the stack.  Returns 0 if possible,
   any other value if there was an error (for example, if the stack is
   full or no memory could be allocated). */
int stack_push(stack_ty*, void*);

#endif
