#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

void insert(dlist *this, item* thing, bool atTail) {
    
    dlist list = *this;

    node* head = list.head;
    //node tail = *list.tail;

    struct node_ *new_node = (struct node_ *) malloc (sizeof (struct node_));
    
    new_node->thing = thing; 
    new_node->ptr = head;

    //if (&head != NULL) {
        struct node_ *next = head->ptr;
        head->ptr = (node*) ((uintptr_t)new_node ^ (uintptr_t)next);
    //}

    if (!atTail) {
        list.head = new_node;   
    }
}